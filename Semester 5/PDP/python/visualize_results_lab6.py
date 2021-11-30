import matplotlib.pyplot as plt

with open("E:\\University\\Semester 5\\PDP\\Lab6\\data\\logs.csv") as f:
    lines = [line[:-1] for line in f.readlines()[1:]]
    times = {}

    for line in lines:
        time, threads, vertices, edges = line.split(",")
        key = f"{vertices}_{edges}"
        if key not in times.keys():
            times[key] = {}
        times[key][int(threads)] = float(time)

    for i, (key, value) in enumerate(times.items(), 1):
        plt.subplot(1, len(times), i)
        plt.title(key)
        threads = list(value.keys())
        plt.xticks(threads)
        values = list(value.values())
        plt.plot(threads, values)
        print(values)
    plt.tight_layout()
    plt.show()
