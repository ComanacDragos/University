#|
1.
a) Write a function to return the n-th element of a list, or NIL if such an element does not exist.

find(l1,...,lm, n)={
					nil, m=0
					l1, n=1
					find(l2,...,lm, n-1), otherwise
}

|#

;;find_nth(l:list, n:integer)
(defun find_nth(l n)
	(cond
		(
			(null l)
				nil
		)
		(
		(eq n 1)
			(car l)
		)
		(
			t
				(find_nth
					(cdr l)
					(- n 1)
				)
		)
	)
)

#|
b) Write a function to check whether an atom E is a member of a list which is not necessarily linear.

is_member(l, e)={
				true, l is an atom and l=e
				false, l is an atom and l!=e
				is_member(l1, e) or is_member(l2,...,ln, e), l=(l1,...,ln) otherwise
}
|#

;;is_member(l:object, e:atom)
(defun is_member(l e)
	(cond
		(
			(and (atom l) (eq l e)) t
		)
		(
			(and (atom l) (NOT (eq l e))) nil	
		)
		(
			t (or (is_member (car l) e) (is_member (cdr l) e))
		)
	)
)

#|
c) Write a function to determine the list of all sublists of a given list, on any level.
 A sublist is either the list itself, or any element that is a list, at any level. Example:
 (1 2 (3 (4 5) (6 7)) 8 (9 10)) => 5 sublists :
 ( (1 2 (3 (4 5) (6 7)) 8 (9 10)) (3 (4 5) (6 7)) (4 5) (6 7) (9 10) )

sublists_aux(l1,..,ln, col1,...,coln) = {
									col1,...,coln, l is empty
									sublists_aux(l2,..,ln, col1,...,coln), l1 is atom
									sublists_aux(l2,...,ln, sublists_aux(l1, l1 U col1,...,coln)), otherwise

									
}

sublists(l) = sublists_aux(l, [l])

|#

;;sublists_aux(l:list, col:list)
(defun sublists_aux(l col)
	(cond
		(
			(null l) col
		)
		(
			(atom (car l)) (sublists_aux (cdr l) col)
		)
		(
			t (sublists_aux 
					(cdr l)
					(sublists_aux 
						(car l)
						(cons (car l) col)
					)
				) 
		)
	)
)

;;sublists(l:list)
(defun sublists(l) (sublists_aux l (cons l nil)))

#|
d) Write a function to transform a linear list into a set.

list2set(l1,...,ln)={
					[], n=0
					list2set(l2,...,ln), is_member(l2,...,ln, l1) = true
					l1 U list2set(l2,...,ln), otherwise
}
|#

;;list2set(l:list)
(defun list2set(l)
	(cond
		(
			(null l) nil
		)
		(
			(is_member (cdr l) (car l)) (list2set (cdr l))
		)
		(
			t 
				(cons 
					(car l)
					(list2set (cdr l))			
				) 
		)
	)
)

