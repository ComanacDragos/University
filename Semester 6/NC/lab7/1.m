#{
Discrete least squares aproximation

* linear least squares approximation

(xi, yi) i=0..m
     f(xi)
     
P(x) = ax+b

E(a,b) = sum i=0..m (yi-P(xi))^2 -> minimum

partial derivative of E wrt a =0, same for b

E(a,b) = sum i=0..m (yi-(a*xi))^2


derivative wrt a = 2*sum i=0..m (yi - (axi+b))*-xi = 0
                 <=> 2*sum i=0..m (-xi*yi + axi^2+b*xi) = 0
                 <=> a sum i=0..m xi^2 + b * sum i=0..m xi = sum i=0..m xi*yi
                 
                 
derivative wrt to b -> a sum i=0..m xi + b(m+1) = sum i=0..m yi

see lecture 6 slide 6 eq 2

* polynomial least squares approximation

(xi, yi), i=0,m

P(x) = anx^n + ...

lecture 6, slides 8-10 for computations



                 

#}



t = [1 2 3 4 5 6 7];
temp = [13 15 20 14 15 13 10];

A = zeros(2, 2);

A(1,1) = sum(t.^2);
A(1,2) = sum(t);
A(2,1) = A(1,2);
A(2,2) = length(t);

b = zeros(2,1);

b(1,1) = sum(t.*temp);
b(2,1) = sum(temp);


coef = A\b;


predicted = polyval(coef, 8)


predicted_values = polyval(coef, t);

e = sum((temp-predicted_values).^2)

plot(t, temp, 'r*',t, temp, 'g-', t, predicted_values, 'b-');





