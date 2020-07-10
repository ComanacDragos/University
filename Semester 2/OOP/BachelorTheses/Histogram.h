#pragma once

#include <QWidget>
//#include "ui_Histogram.h"
#include "Service.h"
#include <qpainter.h>
#include <qpen.h>

class Histogram : public QWidget, public Observer
{
	Q_OBJECT

public:
	Histogram(Service& srv,QWidget *parent = Q_NULLPTR);
	~Histogram();

private:
	Service& srv;

	void paintEvent(QPaintEvent* event);
	//Ui::Histogram ui;
	void update()override { QWidget::update(); }
};
