#|
Write a function that produces the linear list of all atoms of a given list, from all levels, and written in
the same order. Eg.: (((A B) C) (D E)) --> (A B C D E)


linearize(l) = {
	(l), l is atom
	U i=1,n linearize(li), l = (l1,...,ln)
}
|#

(defun linearize (l)
	(cond
		(
			(atom l) (list l)
		)
		(
			t
			;(apply #'append (mapcar #'linearize l))
			(mapcan #'linearize l)
		)
	)

)