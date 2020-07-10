#pragma once

#include <QtWidgets/QMainWindow>
#include <qlabel.h>
#include <QHBoxLayout>

#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <qmessagebox.h>
#include <QDebug>
#include <QObject>
#include <QtQuick/QQuickPaintedItem>
#include <QPainter>
#include <qchar.h>
#include <QWidget>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QStackedWidget>
#include "service.h"
class GUI : public QWidget
{
    Q_OBJECT

public:
    GUI(Service& service,QWidget *parent = Q_NULLPTR);

private:

	Service& srv;
	//QWidget* administratorLayout, * userLayout;
	//QListWidget* coatsList, * userList;
	//QLineEdit* idEdit, * sizeEdit, * priceEdit, * source, * userCoatEdit, * userCoatSizeEdit, * userCoatPriceEdit;
	//QPushButton* addCoatButton, * deleteCoatButton, * updateCoatButton, * filterCoatsButton, * openUserCoatsButton, * nextCoatButton, * listButton, * saveToMyListButton, * showUserListButton, * undoButton, * redoButton, * exitButton, * barChart, * exitAdministratorMode;
	QListWidget* meciuriList;
	QPushButton* addMeci;
	QLineEdit* idEdit, *numeAcasaEdit, *numeDeplasareEdit, * pctAcasa, *pctDeplasare;

	void list();

	void add();
};
