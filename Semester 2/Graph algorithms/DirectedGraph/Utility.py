from texttable import Texttable
import math

class Matrix:
    def __init__(self, lines, columns, defaultValue = 0):
        self._matrix = []
        self._lines = lines
        self._columns = columns
        for i in range(lines):
            line = [defaultValue] * columns
            self._matrix.append(line)

    @property
    def lines(self):
        return self._lines

    @property
    def columns(self):
        return self._columns

    def __getitem__(self, item):
        return self._matrix[item]

    def __setitem__(self, key, value):
        self._matrix[key] = value

    def __str__(self):
        s = ""
        t = Texttable()
        line = list(range(self.columns))
        line.insert(0, "")
        t.add_row(line)

        count = 0
        for i in self._matrix:
            line = i
            line.insert(0, count)
            t.add_row(line)
            count += 1

        return t.draw()

    def __mul__(self, other):
        if(self.columns != other.lines):
            return self

        aux = Matrix(self.lines, other.columns)
        for i in range(self.lines):
            for j in range(other.columns):
                sum = 0
                for k in range(self.lines):
                    sum += self[i][k] * other[k][j]
                aux[i][j] = sum
        return aux

    def extend(self):
        aux=Matrix(self.lines, self.lines, math.inf)
        for i in range(self.lines):
            for j in range(self.lines):
                for k in range(self.lines):
                    aux[i][j] = min(aux[i][j], aux[i][k] +  self._matrix[k][j])
        return aux

    def power(self, power):
        if self.lines != self.columns:
            return
        if power == 0:
            unit = Matrix(self.lines, self.columns)
            for i in range(self.lines):
                unit[i][i] = 1
            return unit
        if power == 1:
            return self

        if power%2 == 0:
            return self.power(int(power/2)) * self.power(int(power/2))
        else:
            return self.power(int(power/2)) * self.power(int(power/2)) * self



'''
m1=Matrix(2,2)
m2=Matrix(2,1)

m1[0][0] = 0
m1[0][1] = 2
m1[1][0] = 1
m1[1][1] = 0

print(m1)
'''