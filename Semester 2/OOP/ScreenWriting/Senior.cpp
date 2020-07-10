#include "Senior.h"

Senior::Senior(Service& srv, Writer writer, TableModel* model,QWidget *parent)
	:GUI{ srv, writer,model, parent }
{
	//ui.setupUi(this);
	this->accept = new QPushButton{ "Accept" };
	ui.verticalLayout_2->addWidget(this->accept);

	ui.ideeasView->setSelectionBehavior(QAbstractItemView::SelectRows);

	QObject::connect(this->accept, &QPushButton::clicked, this, [this]() {this->acceptIdea(); });

}

Senior::~Senior()
{
}

void Senior::acceptIdea()
{
	auto indexes = ui.ideeasView->selectionModel()->selectedIndexes();

	std::string desc = ui.ideeasView->model()->data(indexes[0]).toString().toStdString();
	std::string status = ui.ideeasView->model()->data(indexes[1]).toString().toStdString();
	std::string creator = ui.ideeasView->model()->data(indexes[2]).toString().toStdString();
	int act = ui.ideeasView->model()->data(indexes[3]).toInt();

	this->srv.acceptIdea(desc, status, creator, act);
}
