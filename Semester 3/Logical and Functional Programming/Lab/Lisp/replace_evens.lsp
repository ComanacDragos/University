(defun inlocuire1 (l)
	(cond
		((null l)
			nil
		)
		((and (numberp (car l)) (equal 0 (mod (car l) 2)))
			(cons
				(+ (car l) 1)
				(inlocuire1 (cdr l))
			)
		)
		((atom (car l))
			(cons 
				(car l)
				(inlocuire1 (cdr l))
			)
		)
		(t
			(cons
				(inlocuire1 (car l))
				(inlocuire1 (cdr l))
			)
		)
	)
)

(defun inlocuire2 (l)
	(cond 
		((and (numberp l) (equal 0 (mod l 2)))
			(+ l 1)
		)
		((atom l) l)
		(t
			(cons
				(inlocuire2 (car l))
				(inlocuire2 (cdr l))
			)
		)
	)
)