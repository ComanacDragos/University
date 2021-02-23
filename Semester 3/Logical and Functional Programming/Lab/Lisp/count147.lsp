(defun linearize (l)
	(cond 
		((numberp l) (list l))
		((atom l) nil)
		(t (mapcan #'linearize l))
	)
)

(defun mycount (l)
	(cond
		((null l)0)
		((numberp (car l)) (mycount (cdr l)))
		((listp (car l))(mycount (cdr l)))
		(t   (+ 1 (mycount (cdr l))))
	)
)

(defun main(l)
	(cond 
		((atom l)0)
		((evenp (car (linearize l))) 
			(+ (mycount l) (apply #'+ (mapcar #'main l)))
			)
		(t (apply #'+ (mapcar #'main l)))
	)
)