from owlready2.pymedtermino2.umls import get_ontology

print("Starting...")
onto = get_ontology("ontology.owl")

onto.load()

a= 0