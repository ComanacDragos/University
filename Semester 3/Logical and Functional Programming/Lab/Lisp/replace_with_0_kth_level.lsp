(defun inlocuire (l a k)
	(cond
		((null l) 
			nil
		)
		((and (atom (car l)) (equal a k))
			(cons 0 (inlocuire (cdr l) a k))
		)
		((atom (car l))
			(cons (car l) (inlocuire (cdr l) a k))	
		)
		(t
			(cons
				(inlocuire (car l) (+ a 1) k)
				(inlocuire (cdr l) a k)
			)
		)
	)
)

(defun main (l k) (inlocuire l 1 k))