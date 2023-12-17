from flask import Flask, jsonify, request
from flask_cors import CORS
from ontology import Ontology

app = Flask(__name__)
CORS(app)

onto = Ontology("ontology.owl")


@app.route('/')
def start_page():
    return jsonify("Server is working")


@app.route('/patients')
def get_patients():
    return jsonify(onto.get_patients())


@app.route('/symptoms', methods=['GET'])
def get_symptoms():
    return jsonify(onto.get_symptoms())


@app.route('/symptoms', methods=['POST'])
def add_symptom():
    symptom = request.get_data().decode('utf-8')
    return jsonify("Succesfully added symptom") if onto.add_symptom(symptom) else jsonify("Symptom already exists")


@app.route('/diseases')
def get_diseases():
    return jsonify(onto.get_diseases())


@app.route('/diseases', methods=['POST'])
def add_disease():
    disease = request.get_data().decode('utf-8')
    return jsonify("Succesfully added disease") if onto.add_disease(disease) else jsonify("Disease already exists")


@app.route('/pair', methods=['POST'])
def add_pair():
    data = request.get_data().decode('utf-8')
    data = {k: v for k, v in [x.split("=") for x in data.split('&')]}

    name = data['name'].replace("+", ' ')
    symptom = data['symptom'].replace("+", ' ')
    disease = data['disease'].replace("+", ' ')

    result = onto.add_pair(name, symptom, disease)
    return jsonify(result)


@app.route('/pair', methods=['PUT'])
def get_diseases_for_symptoms():
    data = request.get_data().decode('utf-8')
    data = {k: v for k, v in [x.split("=") for x in data.split('&')]}

    first_symptom = data['firstSymptom'].replace("+", ' ')
    second_symptom = data['secondSymptom'].replace("+", ' ')


    result = onto.get_diseases_for_symptoms([first_symptom, second_symptom])
    return jsonify(result)


port = 7777
print(f"Starting server on port {port}...")

app.run(debug=True, port=port)
