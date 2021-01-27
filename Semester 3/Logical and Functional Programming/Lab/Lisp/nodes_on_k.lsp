(defun nodes (l k i)
	(cond
		((and (atom l) (equal i k))
			1
		)
		((atom l) 
			0
		)
		(t
			(apply #'+ (mapcar #'(lambda (li) (nodes li k (+ i 1))) l))
		)
	)
)

(defun main (l k) (nodes l k 0))