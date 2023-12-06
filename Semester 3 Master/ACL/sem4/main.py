import threading
import time
import xml.etree.ElementTree as ET
import json
import numpy as np
from collections import Counter
from tqdm import tqdm
import matplotlib.pyplot as plt
from utils import run_task
from nltk.stem import WordNetLemmatizer

valid_chars = "abcdefghijklmnopqrstuvwxyz-"


def clean_text(text):
    new_string = ""
    for char in text:
        if char in valid_chars:
            new_string += char

    return new_string


class GetTokens:
    def __init__(self):
        self.wordnet_lock = threading.Lock()
        self.use_lock = True
        self.lemmatizer = WordNetLemmatizer()
        self.lemmatizer.lemmatize("")

    def __call__(self, full_text):
        tokens = []
        for line in full_text.split('\n'):
            text = line.strip().lower()
            types = text.split()

            for type_sample in types:
                for subtype in type_sample.split('-'):
                    subtype = clean_text(subtype)
                    if len(subtype) > 2:
                        tokens.append(self.lemmatizer.lemmatize(subtype))

        return tokens


get_tokens = GetTokens()


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
    with open("vocab_more_stop_words.json") as f:
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
    return term_freq * np.log(number_of_documents / document_freq)


def cosine_similarity(A, B):
    return np.dot(A, B) / (np.linalg.norm(A) * np.linalg.norm(B))


def compute_sim_for_query(query):
    tokens_to_freq = Counter([token for token in get_tokens(query) if token in word_to_docs])

    doc_to_sim = {}

    number_of_documents = len(doc_to_words)

    for doc, word_to_freq in doc_to_words.items():
        common_tokens = set(word_to_freq.keys()).intersection(set(tokens_to_freq.keys()))
        if len(common_tokens) == 0:
            doc_to_sim[doc] = 0.
            continue

        query_representation = []
        doc_representation = []

        all_tokens = set(word_to_freq.keys()).union(set(tokens_to_freq.keys()))

        def compute_tf(word_freq):
            return word_freq / len(all_tokens)
            # return word_freq
            # return np.log(1 + word_freq)
            # return 1 if word_freq >0 else 0

        for word in all_tokens:
            query_freq = tokens_to_freq.get(word, 0)
            doc_freq = word_to_freq.get(word, 0)

            query_representation.append(
                compute_tf_idf(
                    compute_tf(query_freq),
                    sum(word_to_docs[word].values()),
                    number_of_documents
                )
            )
            doc_representation.append(
                compute_tf_idf(
                    compute_tf(doc_freq),
                    sum(word_to_docs[word].values()),
                    number_of_documents
                )
            )

        query_representation = np.asarray(query_representation)
        doc_representation = np.asarray(doc_representation)

        doc_to_sim[doc] = cosine_similarity(query_representation, doc_representation)

    return doc_to_sim


def compute_metrics_at_k(expected, predicted, k):
    predicted_docs = sorted(list(predicted.items()), key=lambda x: x[1], reverse=True)[:k]
    predicted_docs = set([x[0] for x in predicted_docs])
    expected = set(expected)

    relevant_in_top_k = len(expected.intersection(predicted_docs))
    precision_at_k = relevant_in_top_k / k
    recall_at_k = relevant_in_top_k / len(expected)

    # print(k, len(predicted_docs), len(expected), relevant_in_top_k)
    if precision_at_k + recall_at_k == 0:
        f1 = 0.
    else:
        f1 = 2 * precision_at_k * recall_at_k / (precision_at_k + recall_at_k)

    return precision_at_k, recall_at_k, f1


def compute_metrics_at_all_k(expected, predicted):
    precisions_at_k = []
    recalls_at_k = []
    f1s_at_k = []
    for k in range(1, len(expected) + 1):
        precision_at_k, recall_at_k, f1_at_k = compute_metrics_at_k(expected, predicted, k)
        precisions_at_k.append(precision_at_k)
        recalls_at_k.append(recall_at_k)
        f1s_at_k.append(f1_at_k)

    return precisions_at_k, recalls_at_k, f1s_at_k


def test_query(query_id):
    print(queries[query_id])

    doc_to_sim = compute_sim_for_query(queries[query_id])
    tokens_to_freq = Counter([token for token in get_tokens(queries[query_id]) if token in word_to_docs])
    #print(tokens_to_freq)
    print("Sim for doc")
    for doc in mapping[query_id]:
        common = set(doc_to_words[doc].keys()).intersection(tokens_to_freq)
        print(doc, doc_to_sim[doc], common)

    precision, recall, f1 = compute_metrics_at_all_k(mapping[query_id], doc_to_sim)

    plt.plot(recall, precision)

    plt.title("PR cuve")
    plt.show()
    # print("Precision", precision)
    # print("Recall", recall)
    # print("F1", f1)
    number_of_relevant = len(mapping[query_id])

    print("AP", np.mean(precision))

    # for r, p, f in zip(recall, precision, f1):
    #     if r-p == 0:
    #         print(r, p, f)

    print("Top 10 sim")
    doc_to_sim = sorted(list(doc_to_sim.items()), key=lambda x: x[1], reverse=True)
    for k, v in doc_to_sim[:10]:
        if v != 0:
            print(k, v, set(doc_to_words[k].keys()).intersection(tokens_to_freq))


def test_all_queries():
    metrics = {}
    lock = threading.Lock()
    filtered_queries = {k: v for k, v in queries.items() if k in mapping}

    def _worker(_queries):
        print(threading.get_ident(), "Starting with", len(_queries))
        for i, (query_id, query) in enumerate(_queries):
            expected = mapping[query_id]

            start = time.perf_counter()
            doc_to_sim = compute_sim_for_query(query)
            end = time.perf_counter()
            sim_time = end - start

            start = time.perf_counter()
            precision, recall, f1 = compute_metrics_at_all_k(expected, doc_to_sim)
            end = time.perf_counter()
            metrics_time = end - start

            lock.acquire()
            metrics[query_id] = {
                "precision": precision,
                "recall": recall,
                "f1": f1,
                "sim_time": sim_time,
                "metrics_time": metrics_time
            }
            print(threading.get_ident(), "Done", query_id, f"{i}/{len(_queries)}", "sim_time", sim_time, "metrics_time",
                  metrics_time)
            lock.release()

    start = time.perf_counter()
    run_task(list(filtered_queries.items()), _worker, [])
    end = time.perf_counter()
    print("computed in:", end - start)
    with open("metrics.json", 'w') as f:
        json.dump(metrics, f)


def process_results():
    with open("metrics.json") as f:
        data = json.load(f)

    all_precisions = []
    aps = []
    beps = []
    all_f1s = []
    sim_times = []
    metric_times = []

    for query_id, metrics in data.items():
        precision = metrics['precision']
        recall = metrics['recall']
        f1 = metrics['f1']

        if len(precision) > 0:
            ap = np.mean(precision)
            print(query_id, ap)
            aps.append(ap)
            all_precisions += precision
        all_f1s += f1
        sim_times.append(metrics['sim_time'])
        metric_times.append(metrics['metrics_time'])

        for p, r, f in zip(precision, recall, f1):
            if p == r:
                beps.append(f)

    print(f"F1 min: {np.min(all_f1s)} max: {np.max(all_f1s)}")
    print(f"F1 in BEP min: {min(beps)} max: {max(beps)}")
    print(f"R-precision min: {min(all_precisions)} max: {max(all_precisions)}")
    print("mAP", np.mean(aps))

    print(f"Similarity time avg: {np.mean(sim_times)} min: {min(sim_times)} max: {max(sim_times)}")
    print(f"Metrics time avg: {np.mean(metric_times)} min: {min(metric_times)} max: {max(metric_times)}")


if __name__ == '__main__':

    mapping = load_mapping()
    count = 0
    documents = set()
    for l in mapping.values():
        count += len(l)
        for doc in l:
            documents.add(doc)
    print("Check number of mappings", count)
    print("Documents in mapping:", len(documents))
    print("Queries in mapping:", len(mapping))
    # print(len(mapping), mapping)
    queries = load_queries()
    print("Number of queries: ", len(queries))

    # content = load_document("cacm/CACM-1410.html")
    #
    # print(content)

    word_to_docs = load_vocab()
    doc_to_words = invert_vocab(word_to_docs)
    print("Number of docs:", len(doc_to_words))
    print("Number of words: ", len(word_to_docs), "Number of docs: ", len(doc_to_words))

    # queries['1'] = "pascal"
    # test_query("28")
    # test_all_queries()
    process_results()
