from owlready2.pymedtermino2.umls import *


class Ontology:
    def __init__(self, path_to_ontology="ontology.owl"):
        self.path_to_ontology = path_to_ontology
        self.onto = get_ontology(path_to_ontology)
        self.onto.load()

    def get_patients(self):
        return [x.name for x in self.onto.individuals() if self.onto.Patient in x.is_a]

    def get_symptoms(self):
        return [x.name for x in self.onto.individuals() if self.onto.Symptom in x.is_a]

    def add_symptom(self, symptom):
        if symptom in self.get_symptoms():
            return False
        self.onto.Symptom(symptom)
        self.save()
        return True

    def save(self):
        self.onto.save(file=self.path_to_ontology, format="rdfxml")

    def get_diseases(self):
        return [x.name for x in self.onto.individuals() if self.onto.Disease in x.is_a]

    def add_disease(self, disease):
        if disease in self.get_diseases():
            return False
        self.onto.Disease(disease)
        self.save()
        return True


if __name__ == '__main__':
    onto = Ontology()

    print(onto.get_patients())
    print(onto.get_diseases())
    print(onto.get_symptoms())

    onto.add_symptom("Chest pain")
    print(onto.get_symptoms())
