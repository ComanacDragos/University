pkg load statistics

a=[1 2 3]; 
a=[1,2,3];
b=[4;5;6];
b=[4 5 6]';

c = a*b;
#d = [4 5 6];
d=b'; # transpose

e = a.*d;
f=a.^2;
g=a.^d;

v=1:6; # step is one
w=2:3:10; # start:step:final

y = 10:-1:0;

exp(a);
exp(1);

sqrt(a);

m=max(a);

[m,k] = max(a);

h = [-2 -9 8];

k = abs(h);

mean(a);

geomean(a);

sum(a);
prod(a);

# second exercise
a = [1 2 13;4 5 6;7 8 9];
b = [4 8 12;-1 0 5; 2 3 8];

[m,n] = size(a);

t=b';
c=a*b;

d=a.*b;
e=a.^2;

size(a);
length(a); # maximum of dimensions

m = mean(a); # columns
m1 = mean(a,2); # on lines

g=geomean(a);
s=sum(a);

max(a);
max(a,2); # max between elements in a and 2

max(a');

max(a, [], dim=2);

diag(a);

m>2;

a>b;


inv(b);

det(b);
b=[16 15 24]';
x=a\b; # solves a*x=b

triu(a);
tril(a);

m= [2 3 5; 7 11 13; 17 19 23];

m(2,1);
m(:,1);


m(2:3, 2:3);


eye(8);
eye(5,7);

M = magic(4);

sum(M);
sum(M,2);

sum(diag(M))
sum(diag(fliplr(M)))

ones(5);