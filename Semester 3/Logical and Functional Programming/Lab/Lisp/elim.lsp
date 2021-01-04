(defun elim (l e)
	(cond
		((null l)
			nil
		)
		((and (atom (car l)) (equal e (car l)))
			(elim (cdr l) e)
		)
		((atom (car l))
			(cons
				(car l)
				(elim (cdr l) e)
			)
		)
		(t
			(cons
				(elim (car l) e)
				(elim (cdr l) e)
			)
		)
	)
)