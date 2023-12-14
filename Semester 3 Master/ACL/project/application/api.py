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


port = 7777
print(f"Starting server on port {port}...")

app.run(debug=True, port=port)
