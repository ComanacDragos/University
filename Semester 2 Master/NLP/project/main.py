from cube.api import Cube

cube = Cube(verbose=True)

cube.load("ro")

text = "Bucuresti este capitala tarii noastre"

senteces = cube(text)

for sentence in senteces:
    for entry in sentence:
        print(f"Word: {entry.word} Lemma: {entry.lemma} Part of speech: {entry.upos}")