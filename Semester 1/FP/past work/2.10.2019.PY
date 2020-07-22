#First set. Problem 2
import math


def checkIfPrime (x):
    '''
    function returns True if x is prime and False if it's not
    input: x-natural number
    '''
    if x==0 or x==1: return False
    if x==2: return True
    if x%2==0: return False
    for d in range(3,int(math.sqrt(x))+1,2):
        if x%d==0: return False
    return True



def twoPrimes (x):
    '''
    function finds two primes p1 and p2 where p1+p2=x
    input: x-natural even number greater than 2
    output: p1,p2 prime natural numbers
    '''
    if checkIfPrime(x-2):
        p1=2
        p2=x-2
    else:
        for d in range(3,int(math.sqrt(x))+1,2):
            if checkIfPrime(d) and checkIfPrime(x-d):
                p1=d
                p2=x-d
    return p1,p2

'''
a=int(input('give a '))
print(twoPrimes(a))
'''

#Second set. Problem 11

def nullArray ():
    '''
    function returns a null array
    '''
    a = []
    for i in range(0,10):
        a.append(0)
    return a
        
def digitOccurence (x):
    '''
    function returns an array of the occurence of the digits of an natural number
    an element of the array with index i is 1 if i is a digit of x and 0 if not
    input- x natural number
    '''
    v = nullArray()
    while x>=1:
        d=int(x%10)
        v[d]=1
        x/=10
    return v


def sameDigits (x,y):
    '''
    function checks if their writing in base 10 uses the same digits
    input: x,y natural numbers
    output: True if their writing in base 10 uses the same digits and False if not
    '''
    v1 = digitOccurence (x)
    v2 = digitOccurence (y)
    for i in range(0,10):
        if v1[i]!=v2[i]:return False
    return True
'''
a=int(input('Give a= '))
b=int(input('Give b= '))
print(sameDigits(a,b))
'''

#Third set. Problem 13
def nrDiv(x):
    '''
    function returns the number of divisors of x
    input: x natural number
    '''
    if x==1 or x==2: return 1
    count=0
    if x%2==0:
        count=1
        while x%2==0:
            x=x/2
    for d in range(3,int(math.sqrt(x))+1,2):
        if x%d==0:
            count=count+1
            while x%d==0:
                x=x/d
    if x>2:count=count+1
    return count


def nth (n):
  '''
   function finds the n-th element of the sequence 1,2,3,2,5,2,3,7,2,3,2,5,... obtained from the
   sequence of natural numbers by replacing composed numbers with their prime divisors
   input- n natural number
   '''
  nr=0  
  for i in range(1,n+1):
    nr=nr+nrDiv(i)
    if nr>=n:
        x=i
        v=nrDiv(x)-nr+n;
        if x%2==0:
            v=v-1;
            while x%2==0:
                x=x/2
        if v==0:
            return (2)
        else:
            for d in range(3,int(math.sqrt(x))+1,2):
                if x%d==0:
                    v=v-1
                    while x%d==0:
                        x=x/d
                    if v==0:
                        return(d)
            if x>2:
                return(int(x))
            break
n=int(input('Give n= '))
print(nth(n))
