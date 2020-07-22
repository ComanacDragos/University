import random




'''
insert sort 
    - insert each element intro its correct place in a sorted list
'''

def insertSort (data):
    for i in range(1, len(data)): # data[0:i] is already sorted
        elem = data[i] # current element to move
        # figure out where to move elem
        j = i-1
        while j >= 0 and data[j] > elem:
            data[j+1] = data[j]
            j -= 1
        data[j+1] = elem


'''
MERGE sort
    - divide the list in halves
    - sort the halves
    - merge the two halves (merge = interclasare)
    
'''
def merge (data1, data2):
    pass

def mergeSort (data):
    m = len(data)//2
    left = mergeSort(data[:m]) # extra list copying on the side
    right = mergeSort(data[m:])
    return merge(left, right)



data = list(range(10))
random.shuffle(data)
print(data)

print(data)

