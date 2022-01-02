import matplotlib.pyplot as plt

with open("E:\\University\\Semester 5\\PDP\\project\\mpiProject\\data\\logs.csv") as f:
    lines = [line[:-1] for line in f.readlines()[1:]]
    times = {}
    sizes = []
    transformers = []
    for line in lines:
        time, threads, transformerVariant, size, _ = line.split(",")
        if size not in times.keys():
            times[size] = {}
            sizes.append(size)
        if transformerVariant[-3:] == "MPI":
            transformer = transformerVariant[:-3]
            index = 1
        else:
            transformer = transformerVariant[:-7]
            index = 0
        if transformer not in times[size]:
            times[size][transformer] = [[], []]
            if transformer not in transformers:
                transformers.append(transformer)

        times[size][transformer][index].append((int(threads), float(time)))

    fig, axes = plt.subplots(len(transformers), len(sizes), figsize=(10, 10))
    for i, transformer in enumerate(transformers):
        for j, size in enumerate(sizes):
            print(transformer, size)

            pairs = times[size][transformer]
            plt.subplot(len(transformers), len(sizes), i*len(sizes)+j+1)
            plt.title(f"{transformer}_{size}")
            threads = [x[0] for x in pairs[0]]
            plt.xticks(threads)
            values = [x[1] for x in pairs[0]]
            plt.plot(threads, values, label="Threads")

            mpi = [x[0] for x in pairs[1]]
            plt.xticks(mpi)
            values = [x[1] for x in pairs[1]]
            plt.plot(mpi, values, label="MPI")
            plt.legend()
            #print(values)
    plt.tight_layout()
    plt.show()