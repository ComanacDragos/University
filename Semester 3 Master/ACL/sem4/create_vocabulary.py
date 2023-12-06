import sys
from main import load_document, get_tokens
import os
import json
import time
from nltk.corpus import stopwords

start = time.perf_counter()

valid_chars = "abcdefghijklmnopqrstuvwxyz-'ăîșțâ1234567890,<>,."

# process_line = lambda x: x.split("+++$+++")[-1].strip().lower()
process_line = lambda x: x.strip().lower()

# stop_words = ['a', 'the', 'are', 'is']
stop_words = stopwords.words('english')

terms = {}
for txt in os.listdir('cacm'):
    tokens = get_tokens(load_document(f"cacm/{txt}"))

    for term in tokens:
        if term in stop_words:
            continue
        if term in terms:
            if txt in terms[term]:
                terms[term][txt] += 1
            else:
                terms[term] = {txt: 1, **terms[term]}
        else:
            terms[term] = {txt: 1}
end = time.perf_counter()
print(len(terms))
with open("vocab_more_stop_words.json", 'w') as f:
    json.dump(terms, f)

print(end - start)
