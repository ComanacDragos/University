#pragma once

#include <QWidget>
//#include "ui_Painter.h"

#include "Service.h"
#include <qpainter.h>
#include <qpen.h>


class Painter : public QWidget
{
	Q_OBJECT

public:
	Painter(Service& srv,const std::string name,QWidget *parent = Q_NULLPTR);
	~Painter();

private:
	//Ui::Painter ui;

	Service& srv;
	std::string name;

	void paintEvent(QPaintEvent* event);


	//void update()override { QWidget::update(); }
};
