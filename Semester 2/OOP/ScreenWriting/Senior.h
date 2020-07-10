#pragma once

#include <QWidget>
//#include "ui_Senior.h"
#include "GUI.h"

class Senior : public GUI
{
	Q_OBJECT

public:
	Senior(Service& srv, Writer writer,TableModel* model,QWidget *parent = Q_NULLPTR);
	~Senior();

private:
	//Ui::Senior ui;
	QPushButton* accept;

	void acceptIdea();
};
