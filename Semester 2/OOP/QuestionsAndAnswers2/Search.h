#pragma once

#include <QWidget>
#include "ui_Search.h"
#include "Service.h"

class Search : public QWidget
{
	Q_OBJECT

public:
	Search(Service& srv,QWidget *parent = Q_NULLPTR);
	~Search();

private:
	Ui::Search ui;
	Service& srv;

	void loadData();
};
