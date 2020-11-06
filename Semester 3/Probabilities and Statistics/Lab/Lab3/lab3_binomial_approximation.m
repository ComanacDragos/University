pkg load statistics

normalp = input("normal p: ");
poissp = input("poisson p: ");

plot(x, binopdf(x, n, poissp), 'r', poisspdf(x, lambda), 'b');
  
for n=30:200
  lambda = n*poissp;
  mean = n*normalp;
  stdv = sqrt(n*normalp*(1-normalp));
  x = 0:n;
  
  subplot(1,2,1);
  plot(x, binopdf(x, n, normalp), 'r', normpdf(x, mean, stdv), 'b');
  title("Normal approximation");
  legend("binopdf", "normpdf");
  
  subplot(1,2,2);
  title("Poisson approximation");
  legend("binopdf", "poisspdf");
  
  pause(0.5); 
endfor
