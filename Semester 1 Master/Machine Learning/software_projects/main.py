import os
import numpy as np

a = np.asarray([
    [1,2],
    [3,4],
    [5,6]
])
#print(np.sum(a, axis=0))
#print(np.sum(a, axis=1))

#print(1/a)
#print(a+1/a)

b = np.asarray([0, 1, 0])

c = a[(list(range(len(a))), b)]
print(c)
