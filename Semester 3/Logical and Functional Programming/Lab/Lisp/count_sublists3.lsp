(defun linearize (l)
	(cond
		((numberp l) (list l))
		((atom l) nil)
		(t
			(apply #'append 
				(mapcar #'linearize l)
			)
		)
	)

)

(defun check(l) 
	(cond
		((null l)
			nil
		)
		(t
			(equal 0 (mod (car (linearize l)) 2))
		)
	)
)

(defun count_sublists (l)
	(cond 
		((atom l) 0)
		((check l)
			(+ 1 
				(apply #'+ (mapcar #'count_sublists l))
			)
		)
		(t
			(apply #'+ (mapcar #'count_sublists l))		
		)
	)
)