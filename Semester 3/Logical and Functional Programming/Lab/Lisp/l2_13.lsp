#|
13. For a given tree of type (2) return the path from the root node to a certain given node X.

(A (B) (C (D) (E)))


DFS((node, left, right), el, col1,...,coln) ={
	nil,if the tree is nil 
	col1,...,coln U nod , node = element
	DFS(left, el, col1,...,coln U node), DFS(right, el, col1,...,coln U nod) is nil		
	DFS(right, el, col1,...,coln U node), else	
}
|#

(defun DFS(arb el col)
	(cond
		(
			(null arb) nil
		)
		(
			(equal (car arb) el) (append col (list (car arb)))
		)
		(
			t
			(
				(lambda (res_left res_right)	
					(cond
						(
							(null res_right) res_left
						)
						(
							t res_right
						)
					)
				)
				(DFS (cadr arb) el (append col (list (car arb))))
				(DFS (caddr arb) el (append col (list (car arb))))
			)
		)
	)
)
