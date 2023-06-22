import pandas as pd

data = pd.read_csv("processed.csv")
exp_to_title = {}
for row in data.iterrows():
    exp, title, _, _, _, _ = row[1]
    if exp not in exp_to_title:
        exp_to_title[exp] = set(title)
    else:
        exp_to_title[exp].add(title)

intersection = None
for k, v in exp_to_title.items():
    if intersection is None:
        intersection = v
    else:
        intersection = intersection.intersection(v)

valid_jobs = [x for x in intersection if len(x)>1]
print(valid_jobs)

#data[data['job_title'].isin(valid_jobs)].to_csv("valid_jobs.csv", index=False)