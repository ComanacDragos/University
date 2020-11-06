pkg load statistics

p = input("p: ");

for n=1:10:200
  x = 0:n;
  plot(x, binopdf(x, n, p));
  title("Normal approximation");
  legend("binopdf", "normpdf");
  pause(0.5); 
endfor
