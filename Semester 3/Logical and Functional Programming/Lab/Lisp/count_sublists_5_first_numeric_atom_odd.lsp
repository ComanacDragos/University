
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
	(
		(lambda (res)
			(cond
				((or (null res) (equal 0 (mod (car res) 2)))
					nil	
				)
				(t t)
			)
		)
		(linearize l)
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