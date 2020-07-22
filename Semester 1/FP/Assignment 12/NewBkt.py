class Backtracking:
    def __init__(self, n):
        self.n = n
        self.primes = self.get_primes(n)
        self.sum = [None]*(n//2)
        self.index = 1


    @staticmethod
    def is_prime (n):
        if n == 2:
            return True
        if n == 0 or n == 1 or n%2 == 0:
            return False

        d = 3
        while d*d <= n:
            if n%d == 0:
                return False
            d += 2
        return True


    def get_primes (self, n):
        primes = [2]
        d = 3
        while d <= n:
            if self.is_prime(d) == True:
                primes.append(d)

            d += 2
        return primes

    def consistent (self, v):
        k = v[-1]
        for i in v:
            if k < i:
                return False
        return True

    def solution (self, v):
        sum = 0
        for i in v:
            sum += self.primes[i]
        if sum == self.n:
            return True
        return False

    def print_sol (self, v):
        sum = str(self.index) + ". "
        self.index += 1
        for i in v:
            sum += str(self.primes[i]) + "+"
        print(sum [0:len(sum)-1])

    def bkt (self, k):
        for i in range(0, len(self.primes)):
            if k == self.n//2:
                return
            self.sum[k] = i
            v = self.sum[:k+1]
            if self.consistent(v) == True:
                if self.solution(v) == True:
                    self.print_sol(v)
                else:
                    self.bkt(k+1)

    def iterative_bkt(self):
        self.index = 1
        k = 0
        self.sum = [-1] * (self.n//2+1)
        while k >= 0:
            self.sum[k] += 1
            if self.sum[k] < len(self.primes) and k < self.n//2:
                v = self.sum[:k+1]
                if self.consistent(v) == True:
                    if self.solution(v) == True:
                        self.print_sol(v)
                    else:
                        k += 1
                        self.sum[k] = -1
            else:
                k = k-1

n = int(input(">"))

b = Backtracking(n)
print("Recursive:")
b.bkt(0)
print("\nIterative:")
b.iterative_bkt()

x = input("Press any key to exit")