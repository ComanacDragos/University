#include "GUI.h"

GUI::GUI(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    QObject::connect(ui.listButton, &QPushButton::clicked, this, [this]() {this->list(); });
    QObject::connect(ui.unitButton, &QPushButton::clicked, this, [this]() {this->addNeonatal(); });
    QObject::connect(ui.surgeryButton, &QPushButton::clicked, this, [this]() {this->addSurgery(); });
    
    
}


void GUI::list()
{
    if (ui.departmentsList->count() > 0)
        ui.departmentsList->clear();
    for (auto& i : this->srv.getAllDepartments())
    {
        QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(i->to_string()) };
        ui.departmentsList->addItem(item);
    }
}


void GUI::listEfficient()
{
}

void GUI::addSurgery()
{
    QWidget* addSurgeryWidget = new QWidget{};
    QVBoxLayout* vLayout = new QVBoxLayout{ addSurgeryWidget };
    QFormLayout* form = new QFormLayout{};

    surgeryNameEdit = new QLineEdit{};
    surgeryDoctorsEdit = new QLineEdit{};
    patientsEdit = new QLineEdit{};

    this->addSurgeryBttn = new QPushButton{ "Add" };

    form->addRow("Name", surgeryNameEdit);
    form->addRow("Doctors", surgeryDoctorsEdit);
    form->addRow("Patients", patientsEdit);

    vLayout->addLayout(form);
    vLayout->addWidget(this->addSurgeryBttn);

    addSurgeryWidget->show();
    QObject::connect(this->addSurgeryBttn, &QPushButton::clicked, this, [this]() {this->saveSurgery(); });

}

void GUI::saveSurgery()
{
    std::string name = this->surgeryDoctorsEdit->text().toStdString();
    int doctors = this->surgeryDoctorsEdit->text().toInt();
    int patients = this->patientsEdit->text().toInt();

    HospitalDepartment* department = new Surgery{ name, doctors, patients };
    this->srv.addDepartment(department);


}

void GUI::addNeonatal()
{
    QWidget* addNeonatalWidget = new QWidget{};
    QVBoxLayout* vLayout = new QVBoxLayout{ addNeonatalWidget };
    QFormLayout* form = new QFormLayout{};

    nameEdit = new QLineEdit{};
    doctorsEdit = new QLineEdit{};
    mothersEdit = new QLineEdit{};
    newbornsEdit = new QLineEdit{};
    avgEdit = new QLineEdit{};

    this->addNeonatalBttn = new QPushButton{ "Add" };

    form->addRow("Name", nameEdit);
    form->addRow("Doctors", doctorsEdit);
    form->addRow("Mothers", mothersEdit);
    form->addRow("Newborns", newbornsEdit);
    form->addRow("Average", avgEdit);

    vLayout->addLayout(form);
    vLayout->addWidget(this->addNeonatalBttn);

    addNeonatalWidget->show();
    QObject::connect(this->addNeonatalBttn, &QPushButton::clicked, this, [this]() {this->saveNeonatal(); });

}

void GUI::saveNeonatal()
{
    std::string name = this->nameEdit->text().toStdString();
    int doctors = this->doctorsEdit->text().toInt();
    int mothers = this->mothersEdit->text().toInt();
    int newborns = this->newbornsEdit->text().toInt();
    double avg = this->avgEdit->text().toDouble();

    HospitalDepartment* department = new NeonatalUnit{ name, doctors, mothers, newborns, avg };
    this->srv.addDepartment(department);
}

