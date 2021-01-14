(defun dublare (l n i)
	(cond
		((null l) nil)
		((equal (mod i n) 0)
			(cons (car l)
				(cons (car l)
					  (dublare (cdr l) n (+ i 1))
				)
			)
		)
		(t
			(cons (car l)
				  (dublare (cdr l) n (+ i 1))
				)
		)

	)
)