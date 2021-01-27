(defun levels (l k )
	(cond 
		((atom l) k)
		(t
			(apply #'max (mapcar #'(lambda (li) (levels li (+ k 1))) l)) 
		)
	)
)


(defun count_sublist (l)
	(cond 
		((atom l) 0)
		((evenp (levels l 0))
			(+ 1
				(apply #'+ (mapcar #'count_sublist l))
			)
		)
		(t
			(apply #'+ (mapcar #'count_sublist l))
		)
	)
)