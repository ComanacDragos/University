pkg load statistics

p1 = binopdf(7, 10, 0.8)
p2 = binopdf(7, 10, 0.9)
p3 = binopdf(7, 10, 0.75)

p = p1 + p2 + p3 - (p1*p2 + p1*p3 + p2*p3) + p1*p2*p3