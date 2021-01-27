(defun count_numbers (l)
	(cond
		((numberp l) 1)
		((atom l) 0)
		(t 
			(apply #'+ (mapcar #'count_numbers l))
		)
	)
)

(defun check (l)
	(cond 
		((oddp (count_numbers l)) t)
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