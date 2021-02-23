(defun filter (l k c)
	(cond
		((and (numberp l) (equal k c))(list l))
		((atom l)nil)
		(t (mapcan #'(lambda (li) (filter li k (+ 1 c)))l))
	)
)

(defun aux (l k)
	(cond 
		((null (filter l k 0))nil)
		((evenp k) (apply #'max (filter l k 0)))
		(t (apply #'min (filter l k 0)))
	)
)

(defun wrapper (l k)
	((lambda (res)
		(cond 
			((null res) nil)
			(t (cons res (wrapper l (+ k 1))))
		)
	)
	(aux l k)
	)
)

(defun invert (l col)
	(cond ((null l) col)
		(t (invert (cdr l) (cons (car l) col)))
	)
)

(defun main (l) (invert (wrapper l 1) ()))


(defun inlocuire (l el k)
	(cond
		((and (atom l) (evenp k)) l)
		((atom l) el)
		(t (mapcar #'(lambda (li) (inlocuire li el (+ k 1)))l))
	)
)

(defun main2 (l el)
	(inlocuire l el -1)
)