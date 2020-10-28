class Nod:
    def __init__(self, e):
        self.e = e
        self.urm = None
    
class Lista:
    def __init__(self):
        self.prim = None
        

'''
crearea unei liste din valori citite pana la 0
'''
def creareLista():
    lista = Lista()
    lista.prim = creareLista_rec()
    return lista

def creareLista_rec():
    x = int(input("x="))
    if x == 0:
        return None
    else:
        nod = Nod(x)
        nod.urm = creareLista_rec()
        return nod
    
'''
tiparirea elementelor unei liste
'''
def tipar(lista):
    tipar_rec(lista.prim)
    print()
    
def tipar_rec(nod):
    if nod != None:
        print (nod.e, end=" ")
        tipar_rec(nod.urm)
        

'''
program pentru test
'''


def find(el, node):
    """
    find(el, l1,..ln) = {
                        false, n=0
                        true, el = l1
                        find(el, l2,...ln), otherwise
                    }
    """
    if node is None:
        return False
    if node.e == el:
        return True
    return find(el, node.urm)


def list2set_rec(node, previous):
    """
        list2set_rec(l1,...ln) = {
                            [l1], n=1
                            l1 U list2set_rec( l2...ln), find(l1, l2...ln) = false
                            list2set(l2...ln), otherwise

                            1 2 2 3
    """
    if node.urm is None:
        return node
    if find(node.e, node.urm) is True:
        if previous is None:
            return list2set_rec(node.urm, None)
        newNode = Nod(node.urm.e)
        if node.urm.urm is not None:
            newNode.urm = list2set_rec(node.urm.urm, newNode)

        return newNode
    else:
        newNode = Nod(node.e)
        newNode.urm = list2set_rec(node.urm, newNode)
        return newNode

def list2set(list):
    """
    list2set(l1,...ln) = list2set_rec(l1,...ln)
    """
    l = Lista()
    l.prim = list2set_rec(list.prim, None)
    return l

def copy_list(node):
    if node.urm is None:
        return Nod(node.e)
    newNode = Nod(node.e)
    newNode.urm = copy_list(node.urm)

    return newNode

def union_rec(node1, node2):
    """
    union_rec(l1,...,ln, j1,...,jm) = {
                              l1,...ln, m=0
                              j1 U union_rec(l1,...ln, j2,...,jm), find(j1, l1,...ln) = false
                              union_rec(l1,...,ln, j2,...,jm)
    """
    if node2 is None:
        return node1
    if find(node2.e, node1) is False:
        newNode = Nod(node2.e)
        newNode.urm = node1

        return union_rec(newNode, node2.urm)
    else:
        return union_rec(node1, node2.urm)


def union(set1, set2):
    """
    union(l1,...,ln, m1,...,mn) = union_rec(l1,...,ln, m1,...,mn)
    """
    newList = Lista()
    newList.prim = copy_list(set1.prim)
    node = union_rec(newList.prim, set2.prim)
    newList.prim = node
    return newList

def main():
    list = creareLista()
    tipar(list)

    print(find(3, list.prim))

    set1 = list2set(list)
    tipar(set1)
    tipar(list)

    print("Union:")

    list2 = creareLista()
    tipar(list2)
    print()
    set2 = list2set(list2)
    tipar(set2)
    tipar(list2)

    print()
    u = union(set1, set2)

    tipar(u)
    tipar(set1)
    tipar(set2)
main()
    
    
    
    
    