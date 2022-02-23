x = 0:0.01:1;
f = exp(10*x.*(x-1)).*sin(12*pi*x); 
#plot(x, f, '--r');
#plot(x, f, 'o');


# ex 2
a=2;
b=3;
t = 0:0.01:10*pi;

x = (a+b) * cos(t) - b*cos((a/b+1)*t);
y = (a+b) * sin(t) - b*sin((a/b+1)*t); 

#plot(x, y);


# ex 3

x = 0:0.01:2*pi;

f1 = cos(x);
f2 = sin(x);
f3 = cos(2*x);

#plot(x, f1, 'r', x, f2, 'b', x, f3, 'g');

# ex 4

x = -1:0.01:0;
f = x.^3 + sqrt(1-x);

#plot(x, f);hold;

x = 0:0.01:1;
f = x.^3 - sqrt(1-x);


#plot(x, f);hold;

# ex 5

x = 0:2:50;
f = x/2;

#plot(x, f, "*"); hold;

x=1:2:50;
f=3*x+1;

#plot(x, f, "*");hold


# ex 6

function retval= rec(n)
   if(n==0)
    retval = 1;
   else
     retval = 1 + 1/rec(n-1);
   endif
endfunction

rec(5);


# ex 7

[x, y] = meshgrid(-2:0.01:2, -4:0.01:4);

g = exp(-((x-1/2).^2 + (y-1/2).^2));

surf(x, y, g);
