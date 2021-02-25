from math import *


# 1
def f01(text):
    return max(text.split())


# print(f01("Ana are mere rosii si galbene” este cuvântul "))

# 2
def f02(p1, p2):
    return sqrt((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2)


# print(f02((1,5), (4,1)))

# 3
def f03(v1, v2):
    return sum([x * y for x, y in zip(v1, v2)])


# print(f03([1, 0, 2, 0, 3], [1, 2, 0, 3, 1]))

# 4
def f04(text):
    d = {}
    for w in text.split():
        if w in d.keys():
            d[w] += 1
        else:
            d[w] = 1
    return [key for (key, value) in d.items() if value == 1]


# print(f04("ana are ana are mere rosii ana"))

# 5
def f05(v):
    d = {}
    for i in v:
        if i in d:
            return i
        else:
            d[i] = 1


# print(f05([1,2,3,4,2]))


# 6
def f06(v):
    d = {}
    n = len(v) // 2
    for i in v:
        if i in d:
            d[i] += 1
            if d[i] == n:
                return i
        else:
            d[i] = 1


# print(f06([2, 8, 7, 2, 2, 5, 2, 3, 1, 2, 2]))

# 7
def f07(v, k):
    # v = sorted(v, reverse=True)
    v.sort(reverse=True)
    return v[k - 1]


# print(f07([7, 4, 6, 3, 9, 1], 2))

# 8
def f08(n):
    return [int(str(bin(x))[2:]) for x in range(1, n + 1)]


# print(f08(4))

# 9
def f09(m, pairs):
    return [sum(
        [sum(
            [m[i][j] for j in range(x[1], y[1] + 1)]
        ) for i in range(x[0], y[0] + 1)]
    ) for (x, y) in pairs]


print(f09([[0, 2, 5, 4, 1],
           [4, 8, 2, 3, 7],
           [6, 3, 4, 6, 2],
           [7, 3, 1, 8, 3],
           [1, 5, 7, 9, 4]], (((1, 1), (3, 3)), ((1, 2), (1, 3)), ((2, 2), (4, 4)))))


def f10(m):
    return min([(m.index(l), l.index(1)) for l in m], key=lambda x: x[1])[0]


#print(f10([[0, 0, 0, 1, 1],[0, 1, 1, 1, 1],[0, 0, 1, 1, 1]]))

(x,y) = (1,2)

print(x,y)