#pragma once
#include "CoatService.h"
#include "BarChart.h"
#include "UserListTableView.h"
#include <qwidget.h>
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
#include <QShortcut>
#include <QKeySequence>
#include <QModelIndex>

#define AdministratorMenu 0
#define UserMenu 1
#define TableView 2

class GUI : public QMainWindow
{
	Q_OBJECT

public:
	GUI(QWidget* parent = 0);
	~GUI() {}

private:
	QStackedWidget* stackedWidgets;
	QWidget* administratorLayout, * userLayout;
	CoatService coatService;
	QListWidget *coatsList, *userList;
	QLineEdit* nameEdit, * sizeEdit, * priceEdit, * photographSourceEdit, * userCoatEdit, * userCoatSizeEdit, * userCoatPriceEdit;
	QPushButton* addCoatButton, * deleteCoatButton, * updateCoatButton, * filterCoatsButton, * openUserCoatsButton, * nextCoatButton, * listButton, * saveToMyListButton, * showUserListButton, * undoButton, * redoButton, * exitButton, * barChart, * exitAdministratorMode;
	QPushButton* undoUserButton, * redoUserButton;

	QAction* toUserMenu;
	QAction* toAdministratorMenu;
	QAction* toTableView;
	
	UserListTableView* userTableViewWidget;

	void initializeGUI();
	void initializeAdministratorGUI();
	void initializeUserGUI();
	void initializeBarChart();

	void initializeConnections();

	void readSettings();

	int getSelectedIndex(QListWidget* list);
	void listItemSelected();
	void listItemSelectedUserList();
	
	void storeCoat();
	void listCoats();
	void deleteCoat();
	void updateCoat();
	void filterCoats();
	void undo();
	void redo();
	void userUndo();
	void userRedo();
	void saveCoatToUserList();
	void nextCoat();
	void openUserList();
};

