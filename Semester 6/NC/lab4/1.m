#{
first 3 problems -> Newton polynomial
xi interpolation nodes i=0,m and the 
values of a function on these nodes
(Nmf)(x) = f(x0)+ sum i=1..m (x-xo)*..*(x-xi-1) * (Dif)(x0)

(Njf)(x) = (Nj-1f)(x) + (x-x0)*..*(x-xj-1)*(Djf)(x0)



#}


x_vals = [1, 1.5, 2, 3, 4];
f_vals = [0, 0.17609, 0.30103, 0.47712, 0.60206];

x = [2.5, 3.25];

pred_vals = newton(x, x_vals, f_vals)
actual_vals = log(x)./log(10)


y = (10:35)./10;

actual_f = log(y)./log(10);
pred_f = newton(y, x_vals, f_vals);

E = max(abs(actual_f - pred_f))