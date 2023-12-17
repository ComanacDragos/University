from owlready2.pymedtermino2.umls import *


class Ontology:
    def __init__(self, path_to_ontology="ontology.owl"):
        self.path_to_ontology = path_to_ontology
        self.onto = get_ontology(path_to_ontology)
        self.onto.load()

    def get_patients(self):
        return [x.name.replace('%20', ' ') for x in self.onto.individuals() if self.onto.Patient in x.is_a]

    def get_symptoms(self):
        return [x.name.replace('%20', ' ') for x in self.onto.individuals() if self.onto.Symptom in x.is_a]

    def add_symptom(self, symptom):
        if symptom in self.get_symptoms():
            return False
        self.onto.Symptom(symptom)
        self.save()
        return True

    def save(self):
        self.onto.save(file=self.path_to_ontology, format="rdfxml")

    def get_diseases(self):
        return [x.name.replace('%20', ' ') for x in self.onto.individuals() if self.onto.Disease in x.is_a]

    def add_disease(self, disease):
        if disease in self.get_diseases():
            return False
        self.onto.Disease(disease)
        self.save()
        return True

    def add_pair(self, name, symptom, disease):
        if symptom not in self.get_symptoms():
            return "Nonexistent symptom"
        if disease not in self.get_diseases():
            return "Nonexistent disease"

        if name not in self.get_patients():
            self.onto.Patient(name)

        self.onto[name].has_disease.append(self.onto[disease.replace(' ', '%20')])
        self.onto[name].has_symptom.append(self.onto[symptom.replace(' ', '%20')])
        self.save()
        return "Successfully added"

    def get_symptoms_for_patient(self, patient):
        return [x.name.replace('%20', ' ') for x in self.onto[patient].has_symptom]

    def get_diseases_for_patient(self, patient):
        return [x.name.replace('%20', ' ') for x in self.onto[patient].has_disease]

    def get_diseases_for_symptoms(self, symptoms):
        diseases = set()
        for symptom in symptoms:
            if symptom not in self.get_symptoms():
                return "Not all symptoms exists"

        for patient in self.onto.individuals():
            if self.onto.Patient in patient.is_a:
                patient_symptoms = self.get_symptoms_for_patient(patient.name)
                ok = True
                for symptom in symptoms:
                    if symptom not in patient_symptoms:
                        ok = False
                        break
                if ok:
                    diseases = diseases.union(set(self.get_diseases_for_patient(patient.name)))
        return list(diseases)


if __name__ == '__main__':
    onto = Ontology()

    print(onto.get_patients())
    print(onto.get_diseases())
    print(onto.get_symptoms())

    onto.add_symptom("Chest pain")
    print(onto.get_symptoms())
