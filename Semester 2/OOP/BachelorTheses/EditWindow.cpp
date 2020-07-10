#include "EditWindow.h"

EditWindow::EditWindow(Service& srv, const std::string& teacher, QWidget *parent)
	:srv{ srv }, teacher{ teacher }, QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromStdString(teacher));
	this->loadData();
	this->setMinimumWidth(550);
	
	QObject::connect(ui.pushButton, &QPushButton::clicked, this, [this]() {this->save(); });
	QObject::connect(ui.pushButton_2, &QPushButton::clicked, this, [this]() {this->close(); });

}

EditWindow::~EditWindow()
{
}

void EditWindow::loadData()
{
	std::vector<Student> students = this->srv.getStudentsOfTeacher(this->teacher);

	std::sort(students.begin(), students.end(), [](Student& s1, Student& s2)->bool {return s1.getYear() > s2.getYear(); });

	ui.students->setRowCount(students.size());
	ui.students->setColumnCount(5);
	
	int row = 0;
	for (Student& s : students)
	{
		QTableWidgetItem* id = new QTableWidgetItem{ QString::fromStdString(s.getId()) };
		QTableWidgetItem* name = new QTableWidgetItem{ QString::fromStdString(s.getName()) };
		QTableWidgetItem* email = new QTableWidgetItem{ QString::fromStdString(s.getEmail()) };
		QTableWidgetItem* year = new QTableWidgetItem{ QString::number(s.getYear()) };
		QTableWidgetItem* thesis = new QTableWidgetItem{ QString::fromStdString(s.getThesis()) };

		id->setFlags(Qt::ItemIsEditable);
		name->setFlags(Qt::ItemIsEditable);
		year->setFlags(Qt::ItemIsEditable);

		ui.students->setItem(row, 0, id);
		ui.students->setItem(row, 1, name);
		ui.students->setItem(row, 2, email);
		ui.students->setItem(row, 3, year);
		ui.students->setItem(row, 4, thesis);
		row += 1;
	}
}

void EditWindow::save()
{
	for (int i = 0; i < ui.students->rowCount(); i += 1)
	{
		std::string id = ui.students->item(i, 0)->text().toStdString();
		std::string email = ui.students->item(i, 2)->text().toStdString();
		std::string thesis = ui.students->item(i, 4)->text().toStdString();
		this->srv.setMail(id, email);
		this->srv.setThesis(id, thesis);
	}
	this->close();
}
