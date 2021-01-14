(defun inlocuieste (a e k)
	(cond
		((and (atom a) (equal k 0))
			e
		)
		((atom a)
			a
		)
		(t
			(mapcar
				#'(lambda (l) (inlocuieste l e (- k 1)))
				a
			)
		)
	)

)

(defun main (a e k) (inlocuieste a e (+ k 1)))