#include "GUI.h"

GUI::GUI(Service& srv, const std::string& name, QWidget *parent)
    :srv{ srv }, name{ name }, QWidget(parent)
{
    ui.setupUi(this);
    this->setWindowTitle(QString::fromStdString(this->name));
    this->srv.addObserver(this);
    this->loadStudents();

    QObject::connect(ui.searchEdit, &QLineEdit::textChanged, this, [this]() {this->loadSearchedStudents(); });
    QObject::connect(ui.addStudent, &QPushButton::clicked, this, [this]() {this->selectStudent(); });
    QObject::connect(ui.editButton, &QPushButton::clicked, this, [this]() {
        EditWindow* window = new EditWindow{ this->srv, this->name };
        window->show();
        });
}

void GUI::loadStudents()
{
    if (ui.myStudentsList->count() > 0)
        ui.myStudentsList->clear();

    std::vector<Student> students = this->srv.getStudentsOfTeacher(this->name);
    std::sort(students.begin(), students.end(), [](Student& s1, Student& s2)->bool {return s1.getYear() > s2.getYear(); });

    for (Student& s : students)
        if(s.getYear()==2020)
            {
                QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(s.to_string(' ')) };
                ui.myStudentsList->addItem(item);
            }
    for (Student& s : students)
        if (s.getYear() != 2020)
        {
            QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(s.to_string(' ')) };
            ui.myStudentsList->addItem(item);
        }
}

void GUI::loadSearchedStudents()
{
    std::string search = ui.searchEdit->text().toStdString();
    if (search.size() == 0)
        return;
    if (ui.allStudentsList->count() > 0)
        ui.allStudentsList->clear();

    for (Student& s : this->srv.getStudentsByString(search))
    {
        QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(s.to_string(' ')) };
        ui.allStudentsList->addItem(item);
    }
}

void GUI::selectStudent()
{
    if (ui.allStudentsList->selectedItems().isEmpty())
        return;
    std::string line = ui.allStudentsList->selectedItems()[0]->text().toStdString();
    std::string id = tokenize(line, ' ')[0];
    this->srv.setStudentTeacher(id, this->name);
}
