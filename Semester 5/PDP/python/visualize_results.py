import matplotlib.pyplot as plt

with open("E:\\University\\Semester 5\\PDP\\Lab7\\data\\logs.csv") as f:
    lines = [line[:-1] for line in f.readlines()[1:]]
    times = {}

    for line in lines:
        time, threads, type, pDegree, _ = line.split(",")
        if int(threads) == 1:
            continue
        if pDegree not in times.keys():
            times[pDegree] = {"regular": {}, "karatsuba": {}, "regularMPI": {}, "karatsubaMPI": {}}
        times[pDegree][type][int(threads)] = float(time)

    for i, (degree, types) in enumerate(times.items(), 1):
        plt.subplot(1, len(times), i)
        plt.title(degree)
        threads = list(types["regular"].keys())
        plt.xticks(threads)
        regularValues = list(types["regular"].values())
        karatsubaValues = list(types["karatsuba"].values())

        regularValuesMPI = list(types["regularMPI"].values())
        karatsubaValuesMPI = list(types["karatsubaMPI"].values())

        plt.plot(threads, regularValues)
        print(regularValues)
        plt.plot(threads, karatsubaValues)
        print(karatsubaValues)

        plt.plot(threads, regularValuesMPI)
        print(regularValuesMPI)
        plt.plot(threads, karatsubaValuesMPI)
        print(karatsubaValuesMPI)

        plt.legend(["regular", "karatsuba", "regularMPI", "karatsubaMPI"])
    plt.tight_layout()
    plt.show()
