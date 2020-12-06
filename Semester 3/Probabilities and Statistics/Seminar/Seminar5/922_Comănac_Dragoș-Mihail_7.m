pkg load statistics

P1 = (1-gamcdf(1/2, 3, 1/2))*0.8 % probability that for the first line it takes more than 30 seconds
P2 = (1-unifcdf(30, 20, 50))*0.2 % probability that for the second line it takes more then 30 seconds

P = P1 + P2