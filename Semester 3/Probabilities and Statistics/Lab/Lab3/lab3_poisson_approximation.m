pkg load statistics

p = input("p: ");

for n=30:200
  lambda = n*p;
  x = 0:n;
  plot(x, binopdf(x, n, p), 'r', poisspdf(x, lambda), 'b');
  title("Poisson approximation");
  legend("binopdf", "poisspdf");
  pause(0.5); 
endfor
