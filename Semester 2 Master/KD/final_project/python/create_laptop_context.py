import pandas as pd

data = pd.read_csv('laptop_price.csv')

laptops = {}

for company in set(data.loc[:, 'Company']):
    laptops_for_company = data[data['Company'] == company].sample(2).drop_duplicates()
    print(company, len(laptops_for_company))
    for _, row in laptops_for_company.iterrows():
        product, cpu, ram, memory, gpu = row['Product'], row['Cpu'], row['Ram'], row['Memory'], row['Gpu']
        values = ['intel' in cpu.lower(), 'nvidia' in gpu.lower(), 'ssd' in memory.lower(), int(ram[:-2]) >= 8]

        laptop_id = f'{company} {product}'

        if laptop_id in laptops:
            laptop_id += " 2"
        print(laptop_id)

        laptops[laptop_id] = "".join(["X" if x else '.' for x in values])
    print()

print(len(laptops))
laptops = {k: v for k, v in sorted(laptops.items())}
print(laptops)

with open("laptops.cxt", 'w') as f:
    f.write(f"B\n\n{len(laptops)}\n{len(list(laptops.values())[0])}\n\n")
    for key in laptops.keys():
        f.write(f"{key}\n")

    f.write("Intel CPU\nNvidia GPU\nSSD\n>=8 GB RAM\n")
    for val in laptops.values():
        f.write(f"{val}\n")
