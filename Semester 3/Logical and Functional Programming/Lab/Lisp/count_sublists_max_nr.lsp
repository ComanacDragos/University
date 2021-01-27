(defun maxim(l k)
	(cond
		((and (numberp l) (oddp k)) l)
		((atom l) -9999)
		(t (apply #'max (mapcar #'(lambda (li) (maxim li (+ k 1))) l))
		)
	)
	
)

(defun check (l)
	(cond
		((evenp (maxim l 0)) t)
		(t nil)
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
		(t 	(apply #'+ (mapcar #'count_sublists l)))
	)
)