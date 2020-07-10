#include "UserListTableView.h"

UserListTableView::UserListTableView(CoatService& service, QWidget *parent)
	: service{ service }, QWidget(parent)
{
	ui.setupUi(this);
	this->tableModel = new CoatsTableModel{ this->service };
	ui.userTableView->setModel(this->tableModel);
	ui.userTableView->setItemDelegate(new PictureDelegate{});

	//ui.userTableView->resizeRowsToContents();
	ui.userTableView->resizeColumnsToContents();
	ui.userTableView->verticalHeader()->hide();	

	
	this->setStyleSheet(
		"QWidget{background-color: black; color: rgb(128, 233, 210);}"
		"QTableView{gridline-color:rgb(128, 233, 210);background:black;}"
		"QTableView::item{background:black;}"
		"QHeaderView::section{background:black;}"
	);
	
	this->setMinimumHeight(250);
	this->setMinimumWidth(800);
	
}

UserListTableView::~UserListTableView()
{
}

void UserListTableView::beginAddRow()
{
	this->tableModel->beginAddRow();
}

void UserListTableView::endAddRow()
{
	this->tableModel->endAddRow();
}

void UserListTableView::beginRemoveRow()
{
	this->tableModel->beginRemoveRow();
}

void UserListTableView::endRemoveRow()
{
	this->tableModel->endRemoveRow();
}

void UserListTableView::update()
{
	//int rows = ui.userTableView->height();
	//int actualRows = this->service.getUserRepositoryLength();
	//for (int i = rows; i < actualRows; i++)
	//	ui.userTableView;
	ui.userTableView->viewport()->update();
}

