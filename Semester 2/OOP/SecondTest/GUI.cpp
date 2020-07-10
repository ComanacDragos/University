#include "GUI.h"

GUI::GUI(Service& service,QWidget *parent)
	:srv{ service }, QWidget(parent)
{
	QVBoxLayout* layout = new QVBoxLayout{ this };

	this->meciuriList = new QListWidget{};

	layout->addWidget(this->meciuriList);

	QFormLayout* formLay = new QFormLayout{};

	this->idEdit = new QLineEdit{};
	this->numeAcasaEdit = new QLineEdit{};
	this->numeDeplasareEdit = new QLineEdit{};
	this->pctAcasa = new QLineEdit{};
	this->pctDeplasare = new QLineEdit{};
	
	formLay->addRow("ID:", this->idEdit);
	formLay->addRow("Nume acasa:", this->numeAcasaEdit);
	formLay->addRow("Nume deplasare:", this->numeDeplasareEdit);
	formLay->addRow("pct acasa:", this->pctAcasa);
	formLay->addRow("pct deplasare:", this->pctDeplasare);


	layout->addLayout(formLay);
}

void GUI::list()
{
	if (this->meciuriList->count() > 0)
		this->meciuriList->clear();

	for (auto& meci : this->srv.getMeciuri())
	{
		QString itemInList = QString::fromStdString(meci.to_string());
		QListWidgetItem* item = new QListWidgetItem{ itemInList };
		

		if (meci.getAcasa() == "Chicago Bulls")
			item->setBackgroundColor(Qt::red);
		

		if (meci.getDeplasare() == "Chicago Bulls")
			item->setBackgroundColor(Qt::blue);

		this->meciuriList->addItem(item);
	}
}

void GUI::add()
{
	std::string id = this->idEdit->text().toStdString();
}
