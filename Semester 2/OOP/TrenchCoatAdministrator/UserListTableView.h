#pragma once

#include <QWidget>
#include <QModelIndex>
#include "ui_UserListTableView.h"
#include "CoatService.h"
#include "CoatsTableModel.h"
#include "PictureDelegate.h"

class UserListTableView : public QWidget, public Observer
{
	Q_OBJECT

public:
	UserListTableView(CoatService& service, QWidget *parent = Q_NULLPTR);
	~UserListTableView();

	void beginAddRow();
	void endAddRow();

	void beginRemoveRow();
	void endRemoveRow();

	void update() override;

private:
	CoatService& service;
	CoatsTableModel* tableModel;
	Ui::UserListTableView ui;

};
