import xml.etree.ElementTree as ET
import string
import json
import numpy as np


def get_tokens(full_text):
    tokens = []
    for line in full_text.split('\n'):
        text = line.strip().lower()
        types = text.split()

        for type_sample in types:
            for subtype in type_sample.split('-'):

                if len(subtype) > 2:
                    tokens.append(subtype)
    return tokens


def load_mapping():
    _mapping = {}
    with open("mapping.txt") as f:
        for line in f.readlines():
            line = line.strip().split()
            id = line[0]
            doc = line[2]
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
    return term_freq * (1+ np.log((1+number_of_documents)/(1+document_freq)))

def test_query(vocab, doc_to_words, query):
    print(query)
    tokens = set([token for token in get_tokens(query) if token in vocab])
    doc_to_freq = {}

    for doc, word_to_freq in doc_to_words.items():
        #doc_to_freq[doc] = len(set(word_to_freq.keys()).intersection(tokens))
        doc_to_freq[doc] = compute_tf_idf() # compute tfidf for documents and

    doc_to_freq = sorted(list(doc_to_freq.items()), key=lambda x: x[1], reverse=True)
    for k, v in doc_to_freq:
        if v != 0:
            print(k, v)
    #print(doc_to_freq)


if __name__ == '__main__':

    mapping = load_mapping()
    count = 0
    for l in mapping.values():
        count += len(l)
    print(count)
    # print(len(mapping), mapping)
    queries = load_queries()
    print(len(queries))

    content = load_document("cacm/CACM-0011.html")

    # print(content)

    vocab = load_vocab()
    print(len(vocab))

    print(mapping['1'])
    test_query(vocab, invert_vocab(vocab), queries['1'])
