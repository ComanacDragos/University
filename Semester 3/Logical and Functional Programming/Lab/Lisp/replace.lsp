(defun mysubstitute(l e)
	(cond
		((null l) nil)
		((numberp (car l))
			(cons 
				e
				(mysubstitute (cdr l) e)
			)
		)
		((atom (car l))
			(cons 
				(car l)
				(mysubstitute (cdr l) e)
			)
		)
		(t
			(cons 
				(mysubstitute (car l) e)
				(mysubstitute (cdr l) e)
			)
		)
	)
)

(defun mysubstitute2 (l e)
	(cond 
		((numberp l) e)
		((atom l) l)
		(t (mapcar #'(lambda (li) (mysubstitute2 li e)) l))
	) 
)