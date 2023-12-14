from owlready2.pymedtermino2.umls import *


class Ontology:
    def __init__(self, path_to_ontology="ontology.owl"):
        self.onto = get_ontology(path_to_ontology)
        self.onto.load()

    def get_patients(self):
        return [x.name for x in self.onto.individuals() if self.onto.Patient in x.is_a]

    def get_symptoms(self):
        return [x.name for x in self.onto.individuals() if self.onto.Symptom in x.is_a]

    def get_diseases(self):
        return [x.name for x in self.onto.individuals() if self.onto.Disease in x.is_a]


if __name__ == '__main__':
    onto = Ontology()

    print(onto.get_patients())
    print(onto.get_diseases())
    print(onto.get_symptoms())
