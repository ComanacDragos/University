(defun ultim (l)
	(cond
		((null l) l)
		((null (cdr l)) (car l))
		(t
			(ultim (cdr l))
		)		
	)
)

(defun linearize (l)
	(cond
		((numberp l) (list l))
		((atom l) nil)
		(t
			(mapcan #'linearize l)
		)
	)
)

(defun check (l)
	(cond
		((equal 1 (mod (ultim (linearize l)) 2)) t)
		(t nil)
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