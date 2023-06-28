import pandas as pd

data = pd.read_csv("laptop_price.csv")

print("start")
for _, row in data.iterrows():
    company, inches, cpu, ram, memory, gpu = row['Company'], row['Inches'], row['Cpu'].lower(), int(row['Ram'][:-2]), row['Memory'].lower(), row[
        'Gpu'].lower()

    if 'intel' in cpu and 'nvdia' in gpu and ram>=8:
        print(company)

print("done")

