(defun subarbore (l e k)
	(cond
		((and (atom l) (equal k -1)) e)
		((atom l) l)
		(t
			(mapcar #'(lambda (li) (subarbore li e (- k 1))) l)
		)
	)
)