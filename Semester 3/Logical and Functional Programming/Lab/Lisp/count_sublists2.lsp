(defun sum (l k)
	(cond
		((and (numberp l) (equal 1 (mod k 2)))
			l
		)
		((atom l)
			0
		)
		(t
			(apply #'+ (mapcar #'(lambda (li) (sum li (+ k 1))) l))
		)
	)

)

(defun main (l)
	(cond
		((atom l) 0)
		((equal 0 (mod (sum l 0) 2))
			(+ 1 (apply #'+ (mapcar #'main l)))
		)
		(t
			(apply #'+ (mapcar #'main l))	
		)
	)
)