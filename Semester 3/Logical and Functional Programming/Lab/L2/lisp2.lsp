#|
3. Return the number of levels of a tree of type (1)
(A 2 B 0 C 2 D 0 E 0)

  A
 / \
B   C
   / \
  D   E

subTreesAux(l1,...,ln, nv, ne, col1,...,coln) = {
	[col1,...,coln, l1,...,ln], nv = 1 + ne or n=0
	subTreesAux(l3,...,ln, nv + 1, ne + l2, col1,...,coln U l1 U l2), else 
}
|#

;;subTreesAux(l:list, nv:integer, ne:integer, col: list)
(defun subTreesAux(l nv ne col)
	(cond
		(
			(or (equal nv (+ 1 ne)) (null l))
				(list col l)
		)
		(
			t
			(subTreesAux
				(cddr l)
				(+ 1 nv)
				(+ ne (cadr l))
				(append
					col
					(list 
						(car l)
						(cadr l)
					)	
				)
			)
		)
	)
)

#|
subTrees(l1,...,ln) = {
					nil, n = 0
					subTreesAux(l3,...,ln, 0, 0, ()), else

|#
;;subTrees(l: list)
(defun subTrees(l)
	(cond
		(
			(null l) nil
		)
		(
			t
			(subTreesAux
				(cddr l)
				0
				0
				()
			)
		)
	)
)

#|

numberOfLevels(l1,..,ln)={
		0, n = 0
		1 + max(numberOfLevels(left), numberOfLevels(right)), left, right = subTrees(l1,...,ln), else
}
|#

(defun numberOfLevels(l)
	(cond
		(
			(null l) 0
		)
		(t
			(
				(lambda (res)	
					(+
						1
						(max
							(numberOfLevels (car res))
							(numberOfLevels (cadr res))
						)
					)
				)
				(subTrees l)
			)
		)

	)
)

