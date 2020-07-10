#pragma once

#include <QWidget>
#include "ui_SearchWindow.h"
#include "Service.h"

class SearchWindow : public QWidget, public Observer
{
	Q_OBJECT

public:
	SearchWindow(Service& srv,QWidget *parent = Q_NULLPTR);
	~SearchWindow();

private:
	Ui::SearchWindow ui;
	Service& srv;

	void loadQuestion();
	void update()override {
		this->loadQuestion();
	}
};
