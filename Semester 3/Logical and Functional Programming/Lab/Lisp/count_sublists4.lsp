(defun maxim(l k)
	(cond
		((and (equal 1 (mod k 2)) (numberp l))
			l
		)
		((atom l) -999)
		(t
			(apply #'max (mapcar #'(lambda (li) (maxim li (+ k 1))) l))
		)
	)
)

(defun numara (l)
	(cond
		((atom l) 0)
		((equal 0 (mod (maxim l 0 ) 2))
			(+ 1
				(apply #'+ (mapcar #'numara l))
			)
		)
		(t
			(apply #'+ (mapcar #'numara l))
		)
	)
)