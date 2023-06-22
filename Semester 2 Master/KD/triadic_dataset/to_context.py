import pandas as pd

data = pd.read_csv("valid_jobs_v3.csv")

with open('context_v3.csv', 'w') as f:
    for i, row in enumerate(data.iterrows()):
        exp, title, remote, _, company_size, salary_type = row[1]
        print(exp, title, remote, company_size, salary_type)
        f.write(f'{title},salary_{salary_type},{exp}\n')
        f.write(f'{title},company_size_{company_size},{exp}\n')
        if remote != 0:
            f.write(f'{title},remote,{exp}\n')

