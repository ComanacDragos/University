from flask import Flask, jsonify
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


@app.route('/symptoms')
def get_symptoms():
    return jsonify(onto.get_symptoms())


@app.route('/diseases')
def get_diseases():
    return jsonify(onto.get_diseases())


port = 7777
print(f"Starting server on port {port}...")

app.run(debug=True, port=port)
