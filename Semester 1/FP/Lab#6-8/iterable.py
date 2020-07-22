class Iterable:
    def __init__(self, data):
        self.data = data

    def __len__(self):
        return len(self.data)

    def __getitem__(self, item):
        return self.data[item]

    def __setitem__(self, key, value):
        self.data[key] = value

    def __delitem__(self, key):
        self.data.pop(key)

    def __iter__(self):
        self.index = 0
        return self

    def __next__(self):
        if self.index == len(self.data):
            raise StopIteration
        index = self.index
        self.index += 1
        return self.data[index]

    def __str__(self):
        return str(self.data)

    def append (self, obj):
        self.data.append(obj)

def gnomeSort(list, key):
    index = 0
    cont = 0
    if len(list) == 1:
        return

    while index < len(list):
        cont += 1

        if index == 0:
            index = 1

        if key(list[index-1], list[index]) == False:
            aux = list[index]
            list[index] = list[index-1]
            list[index-1] = aux
            index -= 1
        else:
            index += 1

def filter (list, key, left, right):
    '''
    If key is true the object gets deleted
    '''
    index = 0
    while index < len(list):
        if key(left, right, list[index]) == True:
            del list[index]
        else:
            index += 1

def key (l,r, obj):
    if obj < l or obj > r:
        return True
    return False






























"""
l = [1, 2, 3, 4, 453, 234, 234, 234, 5, 12, 43, 5, 6, 7]
filter(l, lambda l, r, obj: obj >= l and obj <= r, 8, 500)
#filter(l, key, 4, 7)
print(l)"""
"""
print(iter)
gnomeSort(iter, lambda x, y: x <= y)
print(iter)"""

"""
print(iter)
filter(iter, key, 2,6)
print(iter)
"""


"""iter = Iterable([34, 2, 10, -9])
print(iter)
gnomeSort(iter, comp)
print(iter)
def key (left, right, val):
    if val < left or val > right:
        return False
    return True

"""
