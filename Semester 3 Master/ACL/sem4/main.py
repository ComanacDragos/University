import xml.etree.ElementTree as ET
import json
import numpy as np
from collections import Counter
from tqdm import tqdm
import matplotlib.pyplot as plt

valid_chars = "abcdefghijklmnopqrstuvwxyz-"


def clean_text(text):
    new_string = ""
    for char in text:
        if char in valid_chars:
            new_string += char

    return new_string


def get_tokens(full_text):
    tokens = []
    for line in full_text.split('\n'):
        text = line.strip().lower()
        types = text.split()

        for type_sample in types:
            for subtype in type_sample.split('-'):
                subtype = clean_text(subtype)
                if len(subtype) > 2:
                    tokens.append(subtype)
    return tokens


def load_mapping():
    _mapping = {}
    with open("mapping.txt") as f:
        for line in f.readlines():
            line = line.strip().split()
            id = line[0]
            doc = f"{line[2]}.html"
            if id in _mapping:
                _mapping[id].append(doc)
            else:
                _mapping[id] = [doc]
    return _mapping


def load_queries():
    _queries = {}
    tree = ET.parse('queries.xml')
    root = tree.getroot()
    for i in range(len(root)):
        query = root[i]
        _queries[query[0].text] = query[1].text.strip()
    return _queries


def load_document(doc):
    with open(doc) as f:
        lines = f.readlines()[2:-2]
        digits = '0123456789'

        def contains_digits_only(line):
            for char in line.strip():
                if char not in digits and char not in ' \t':
                    return False
            return True

        lines = [line for line in lines if len(line.strip()) > 0 and not contains_digits_only(line)]

        content = "".join(lines)

        return content


def load_vocab():
    with open("vocab.json") as f:
        vocab = json.load(f)

    return vocab


def invert_vocab(vocab):
    inverted_vocab = {}
    for word, docs in vocab.items():
        for doc, freq in docs.items():
            if doc in inverted_vocab:
                inverted_vocab[doc][word] = freq
            else:
                inverted_vocab[doc] = {word: freq}
    return inverted_vocab


def compute_tf_idf(term_freq, document_freq, number_of_documents):
    # return term_freq * (1 + np.log((1 + number_of_documents) / (1 + document_freq)))
    # return term_freq * (np.log(number_of_documents / (1 + document_freq)))
    return term_freq * np.log2(number_of_documents / (1 + document_freq))


def cosine_similarity(A, B):
    sim = np.dot(A, B) / (np.linalg.norm(A) * np.linalg.norm(B))
    return (sim + 1) / 2  # convert to 0, 1 where 1 means similar


def euclidian_distance(A, B):
    return np.linalg.norm(A - B)


def compute_sym_for_query(query):
    tokens_to_freq = Counter([token for token in get_tokens(query) if token in word_to_docs])

    doc_to_sim = {}

    number_of_documents = len(doc_to_words)
    for doc, word_to_freq in doc_to_words.items():
        # doc_to_freq[doc] = len(set(word_to_freq.keys()).intersection(tokens))

        # common_tokens = set(word_to_freq.keys()).intersection(set(tokens_to_freq.keys()))
        # if len(common_tokens) == 0:
        #     doc_to_sim[doc] = 0.
        #     continue

        query_representation = []
        doc_representation = []

        for word in word_to_freq:
            query_representation.append(
                compute_tf_idf(
                    tokens_to_freq.get(word, 0) / len(tokens_to_freq),
                    len(word_to_docs[word]),
                    number_of_documents
                )
            )
            doc_representation.append(
                compute_tf_idf(
                    word_to_freq.get(word, 0) / len(word_to_freq),
                    len(word_to_docs[word]),
                    number_of_documents
                )
            )

        query_representation = np.asarray(query_representation)
        doc_representation = np.asarray(doc_representation)

        doc_to_sim[doc] = np.dot(query_representation, doc_representation) #cosine_similarity(query_representation, doc_representation)
        # doc_to_sim[doc] = cosine_similarity(query_representation, doc_representation)

    # all_sims = list(doc_to_sim.values())
    # min_sim = np.min(all_sims)
    # max_sim = np.max(all_sims)
    #
    # doc_to_sim = {k: (v-min_sim)/(max_sim-min_sim) for k, v in doc_to_sim.items()}
    return doc_to_sim


def compute_metrics(expected, predicted, threshold):
    predicted = [doc for doc, prob in predicted.items() if prob >= threshold]

    if len(expected) == 0 and len(predicted) == 0:
        return 1., 1., 1.
    if len(expected) == 0 or len(predicted) == 0:
        return 0., 0., 0.

    tp = 0
    fp = 0
    fn = 0

    for doc in expected:
        if doc in predicted:
            tp += 1
        else:
            fn += 1

    for doc in predicted:
        if doc not in expected:
            fp += 1

    precision = tp / (tp + fp)
    recall = tp / (tp + fn)

    if precision + recall == 0:
        f1 = 0.
    else:
        f1 = 2 * precision * recall / (precision + recall)
    return precision, recall, f1


def repeated_trapezium(x, y):
    n = len(x) - 1
    return (x[-1] - x[0]) / (2 * n) * (y[0] + y[-1] + 2 * np.sum(y[:-1]))


def compute_thresholded_metrics(expected, predicted, thresholds=100):
    precisions = []
    recalls = []
    f1s = []
    for threshold in np.linspace(0, 1, thresholds):
        precision, recall, f1 = compute_metrics(expected, predicted, threshold)
        precisions.append(precision)
        recalls.append(recall)
        f1s.append(f1)

    return precisions, recalls, f1s


def compute_ap(precision, recall):
    return repeated_trapezium(recall, precision)


def test_query(query_id):
    print(queries[query_id])

    doc_to_sim = compute_sym_for_query(queries[query_id])

    print("Sim for doc")
    for doc in mapping[query_id]:
        print(doc, doc_to_sim[doc])

    precision, recall, f1 = compute_thresholded_metrics(mapping[query_id], doc_to_sim)

    plt.plot(recall, precision)
    plt.title("PR cuve")
    plt.show()
    # print("Precision", precision)
    # print("Recall", recall)
    print("F1", f1)
    print("AP", compute_ap(precision, recall))

    print("Top 10 sim")
    doc_to_sim = sorted(list(doc_to_sim.items()), key=lambda x: x[1], reverse=True)
    for k, v in doc_to_sim[:10]:
        if v != 0:
            print(k, v)


def test_all_queries():
    aps = []

    for query_id, query in tqdm(queries.items(), total=len(queries), miniters=0):
        expected = mapping.get(query_id, [])
        doc_to_sim = compute_sym_for_query(query)
        precision, recall, f1 = compute_thresholded_metrics(expected, doc_to_sim)
        aps.append(compute_ap(precision, recall))

    print("MAP", np.mean(aps))


if __name__ == '__main__':

    mapping = load_mapping()
    count = 0
    for l in mapping.values():
        count += len(l)
    print("Check number of mappings", count)
    # print(len(mapping), mapping)
    queries = load_queries()
    print("Number of queries: ", len(queries))

    content = load_document("cacm/CACM-0011.html")

    # print(content)

    word_to_docs = load_vocab()
    doc_to_words = invert_vocab(word_to_docs)
    print("Number of words: ", len(word_to_docs), "Number of docs: ", len(doc_to_words))

    test_query("1")
    # test_all_queries()
