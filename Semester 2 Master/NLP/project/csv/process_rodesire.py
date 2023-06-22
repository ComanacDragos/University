import pandas as pd

data = pd.read_csv("RoDesireDBPreprocessed.csv")

data = data.rename({
    "Content": "description",
    "Label": "category"
}, axis=1)

data.to_csv("rodesire.csv", sep=';', index=False)