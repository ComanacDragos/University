(defun path (el l)
	(
		(lambda (res)
			(cond
				((and (null (cdr l)) (equal el (car l)))
					l
				)
				((null (cdr l))
					nil
				)
				((not (null res))
					(cons (car l) res)
				)
				(t nil)
			)
		)
		(mapcan #'(lambda (li) (path el li)) (cdr l))
	)
)