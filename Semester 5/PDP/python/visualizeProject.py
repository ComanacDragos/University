import matplotlib.pyplot as plt

with open("E:\\University\\Semester 5\\PDP\\project\\threads\\data\\logs.csv") as f:
    lines = [line[:-1] for line in f.readlines()[1:]]
    times = {}
    sizes = []
    transformers = []
    for line in lines:
        time, threads, transformer, size, _ = line.split(",")
        if size not in times.keys():
            times[size] = {}
            sizes.append(size)
        if transformer not in times[size]:
            times[size][transformer] = []
            if transformer not in transformers:
                transformers.append(transformer)
        times[size][transformer].append((int(threads), float(time)))

    fig, axes = plt.subplots(len(transformers), len(sizes), figsize=(10, 10))
    for i, transformer in enumerate(transformers):
        for j, size in enumerate(sizes):
            pairs = times[size][transformer]
            plt.subplot(len(transformers), len(sizes), i*len(sizes)+j+1)
            plt.title(f"{transformer}_{size}")
            threads = [x[0] for x in pairs]
            plt.xticks(threads)
            values = [x[1] for x in pairs]
            plt.plot(threads, values)
            print(values)
    plt.tight_layout()
    plt.show()