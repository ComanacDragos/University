t=-1:0.01:1;

T1 = cos(1*acos(t));
T2 = cos(2*acos(t));
T3 = cos(3*acos(t));

plot(t, T1, "r", t, T2, "b", t, T3, "g");