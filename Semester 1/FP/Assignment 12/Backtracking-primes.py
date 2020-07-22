class RecursiveBkt:

    def __init__(self, n):
        self.n = n
        self.primes = self.get_primes(n)
        self.sum = [None]*(n//2)
        self.index = 1

        #self.bkt(1)

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

    def consistent (self, k):
        for i in range(0, k):
            if self.sum[k] == self.sum[i]:
                return False
        return True

    def solution (self, k):
        """sum = 0
        for i in range(0, self.n//2):
            if self.sum[i] == None:
                sum += 0
            else:
                sum += self.primes[self.sum[i]]
        if sum == self.n:
            return True
        return False
"""
        if k == self.n//2-1:
            return True
        return False
    def print_sol (self, k):
        #string = str(self.primes[self.sum[0]])
        string = str(self.index) + ". "
        self.index += 1
        string += str(self.sum[0]+1)

        for i in range(1, self.n//2):
            string += " + "
            #string += str(self.primes[self.sum[i]])
            string += str(self.sum[i]+1)

        string += " = " + str(n)
        print(string)

    def bkt (self, k):
        for i in range(0, self.n//2):
            #if k == self.n//2:
                #return
            self.sum[k] = i
            if self.consistent(k) == True:
                if self.solution(k) == True:
                    self.print_sol(k)
                else:
                    self.bkt(k+1)


n = int(input(">"))
n = n*2
b = RecursiveBkt(n)
b.bkt(0)

l = [1,2,3]
b = l[:2]
print(b)

"""
    def bkt (self, k):
        for i in range(0, len(self.primes)):

            if self.n//2 > k:
                self.sum[k] = i
                if self.solution(self.sum, self.n, k) == True:
                    self.print_sol(self.sum, self.n, k)
                    return
                else:
                    self.bkt(k+1)



    def consistent (self, list, k)

    def solution (self, list, n, k):
        sum = 0
        count = 0
        for i in list:
            count += 1
            if count == k:
                break
            if i == None:
                break
            sum += self.primes[i]

        #print(list)
        if sum == n:
            return True
        return False

    def print_sol (self, list, n, k):
        sol = str(self.primes[list[0]])
        for i in range(1,len(list)):
            if i == k-1:
                break
            sol += " + "
            sol += str(self.primes[list[i]])
        sol += " = " + str(n)
        print(sol)
"""