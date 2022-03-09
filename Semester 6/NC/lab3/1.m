#{
xi i=0..m interpolation points
values for a function at this nodes

L.I.P. => determining polynomial 
of smallest degree that passes throught thse points

s.t. P(xi) = f(xi)

Fundamental form

(Lmf)(x) = sum i=0..m li(x) * f(xi)
li(x) = ui(x)/ui(xi) 
      = product j=0..m!=i (x-xi)/(xi-xj)
      
Barycentric form

(Lmf)(x) = (sum i=0..m Ai/(x-xi)*f(xi))/(sum i=0..m Ai/(x-xi))

Ai = 1/ui(xi) = 1/(prodcut j=0..m!=i (xi-xj))

#}
clear -classes


barycentric([1.5, 1.6, 2.5, 3.6], [1,2,3], [5,6,7])

uint32(
barycentric(
  [1955, 1995],
  [1930, 1940, 1950, 1960, 1970, 1980],
  [123203, 131669, 150697, 179323, 203212, 226505]
)
)