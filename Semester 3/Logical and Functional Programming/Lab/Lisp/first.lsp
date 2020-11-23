#|
a) Sa se insereze intr-o lista liniara un atom a dat dupa al 2-lea, al 4-lea,
al 6-lea,....element.
b) Definiti o functie care obtine dintr-o lista data lista tuturor atomilor
care apar, pe orice nivel, dar in ordine inversa. De exemplu: (((A B) C)
(D E)) --> (E D C B A)
c) Definiti o functie care intoarce cel mai mare divizor comun al numerelor
dintr-o lista neliniara.
d) Sa se scrie o functie care determina numarul de aparitii ale unui atom dat
intr-o lista neliniara.

a)
insert_el(l1,l2,l3...,ln, e) = {
								l1,...,ln, n<=1
								l1 U l2 U e U insert_el(l3,...,ln, e), otherwise
}

b)
invert_list_aux(l1,...,ln, col1,...,colm) = {
										col1,...,coln, n = 0
										invert_list(l2,...,ln, invert_list(l1, col1,..,colm)), l1 is list
										invert_list(l2,...,ln, l1 U col1,...,coln), else
}

invert_list(l) = invert_list_aux(l, [])

c)

cmmdc(a, b) ={
				a, b=0,
				b, a=0,
				a, a=b,
				a-b, a>b,
				b-a, else
}

cmmdc_list(l1,...,ln) ={
						0, n=0
						l1, l1 number and n = 1
						cmmdc_list(l1), l1 list and n=1
						cmmdc(l1, cmmdc_list(l2,...,ln)), l1 number
						cmmdc(cmmdc_list(l1), cmmdc_list(l2,...,ln)), l1 list
}

count_appearances(l, e) = {
				1, l is a atom and l=e
				0, l is a atom and l!=e
				count_appearances(l1, e) + count_appearances(l2,...,ln, e), l=(l1,..,ln) is a list
}

|#

;;insert_el(l: list, e:atom)
(defun insert_el(l e)
	(cond
		((<= (length l) 1) l)
		(T (cons 
				(car l)
				(cons 
					(cadr l)
					(cons
						e 
						(insert_el (cddr l) e)
					)
				)
			)
		)
	)
)


;;invert_list_aux(l:list, col1:list)
(defun invert_list_aux(l col)
	(cond
		(
			(null l) col
		)
		(
			(listp (car l)) (invert_list_aux 
								(cdr l)
								(invert_list_aux
									(car l)
									col
								)
							)
		)
		(t
			(invert_list_aux
				(cdr l)
				(cons 
					(car l)
					col
				)
			)
		)
	)
)

;;invert_list(l:list)
(defun invert_list(l) (invert_list_aux l ()))


;;cmmdc(a:object, b:object)
(defun cmmdc(a b)
	(cond
		(
			(eq a 0 ) b
		)
		(
			(eq b 0 ) a
		)
		(
			(= a b) a
		)
		(
			(< a b) (cmmdc a (- b a))
		)
		(
			t (cmmdc (- a b) b)
		)
	)
)


;;cmmdc_list(l:list)
(defun cmmdc_list(l)
	(cond
		(
			(null l) 0
		)
		(
			(and (null (cdr l)) (numberp (car l))) (car l)
		)
		(
			(and (null (cdr l)) (listp (car l))) (cmmdc_list (car l))
		)
		(
			(numberp (car l)) 
				(cmmdc
					(car l)
					(cmmdc_list (cdr l))
				)
		)
		(
			(listp (car l)) 
				(cmmdc
					(cmmdc_list (car l))
					(cmmdc_list (cdr l))
				)
		)
			
	)
)


;;count(l:object, e:atom)
(defun count_appearances(l e)
	(cond
		(
			(and (atom l) (eq l e)) 1
		)
		(
			(and (atom l) (not (eq l e))) 0
		)
		(
			t (+ (count_appearances (car l) e) (count_appearances (cdr l) e))
		)
	)
)