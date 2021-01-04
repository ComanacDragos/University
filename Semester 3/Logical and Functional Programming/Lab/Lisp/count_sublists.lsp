(defun laura (l k)
	(cond
		((and (numberp l) (equal (mod k 2) 1))
			l
		)
		((atom l)
			9999999
		)
		(t
			(apply 
				#'min 
				(mapcar
					#'(lambda (li) (laura li (+ k 1)))
					l
				)
			)
		)

	)
)

(defun main (l)
	(cond
		((null l) 0)
		((atom (car l))
			(main (cdr l))
		)
		((equal (mod (laura (car l) 0) 2) 0)
			(+ 1 (main (car l)) (main (cdr l)))
		)
		(t
			(+ (main (car l)) (main (cdr l)))
		)

	)

)