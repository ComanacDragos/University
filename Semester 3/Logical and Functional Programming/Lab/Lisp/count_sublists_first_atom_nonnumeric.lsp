(defun linearize(l)
	(cond
		((atom l) (list l))
		(t (mapcan #'linearize l))
	)
)

(defun check (l)
	(cond
		((or (null l) (numberp (car (linearize l)))) nil)
		(t t)
	)	
)


(defun count_sublist (l)
	(cond 
		((atom l) 0)
		((check l)
			(+ 1
				(apply #'+ (mapcar #'count_sublist l))
			)
		)
		(t
			(apply #'+ (mapcar #'count_sublist l))
		)
	)
)