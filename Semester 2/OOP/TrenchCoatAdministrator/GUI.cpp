#include "GUI.h"

GUI::GUI(QWidget* parent) :QMainWindow{ parent }
{
	this->readSettings();
	this->initializeGUI();
	this->listCoats();
	this->setMinimumHeight(500);
	this->setMinimumWidth(600);
}

void GUI::initializeGUI()
{
	QWidget* centralWidget = new QWidget{};
	this->administratorLayout = new QWidget{};
	this->userLayout = new QWidget{};

	this->initializeAdministratorGUI();

	this->initializeUserGUI();

	this->userTableViewWidget = new UserListTableView{ this->coatService };
	
	this->coatService.addObserver(this->userTableViewWidget);

	this->stackedWidgets = new QStackedWidget{};

	this->stackedWidgets->addWidget(this->administratorLayout);
	this->stackedWidgets->addWidget(this->userLayout);
	//this->stackedWidgets->addWidget(this->userTableViewWidget);
	
	this->toUserMenu = new QAction{ "&User Mode", this };
	this->toAdministratorMenu = new QAction{ "&Administrator Mode", this };
	this->toTableView = new QAction{ "&Table view", this };

	this->menuBar()->addAction(this->toAdministratorMenu);
	this->menuBar()->addAction(this->toUserMenu);
	this->menuBar()->addAction(this->toTableView);

	this->setStyleSheet(
		"QWidget{background-color: black; color: rgb(128, 233, 210);}"
		"QPushButton{background-color:rgb(128, 233, 210);color: black; border-radius: 15px;padding:10px;box-shadow: 5px 10px;}"
		"QPushButton:hover{background-color: rgb(0, 153, 120);color: black;}"
		"QMenu{background-color:rgb(128, 233, 210);color: black;}"
		"QMenu::item:selected{background-color: rgb(0, 153, 120);color: black;}"
		"QMenuBar{background-color:black;color: rgb(128, 233, 210);}"
		"QMenuBar::item:selected{background-color: rgb(128, 233, 210);color: black;}"
		"QTableView{gridline-color:black;background:black;}"
		"QTableView::item{background:black;}"
		"QHeaderView::section{background:black;}"
	);

	this->setCentralWidget(this->stackedWidgets);

	this->initializeConnections();
}

void GUI::initializeAdministratorGUI()
{
	QVBoxLayout* administratorLayout = new QVBoxLayout{ this->administratorLayout };

	this->coatsList = new QListWidget{};
	QGridLayout* buttons = new QGridLayout{};
	QFormLayout* formLayout = new QFormLayout{};

	administratorLayout->addWidget(this->coatsList);

	this->nameEdit = new QLineEdit{};
	QLabel* nameLabel = new QLabel{ "&Name:" };
	nameLabel->setBuddy(this->nameEdit);

	this->sizeEdit = new QLineEdit{};
	QLabel* sizeLabel = new QLabel{ "&Size:" };
	sizeLabel->setBuddy(this->sizeEdit);

	this->priceEdit = new QLineEdit{};
	QLabel* priceLabel = new QLabel{ "&Price:" };
	priceLabel->setBuddy(this->priceEdit);

	this->photographSourceEdit = new QLineEdit{};
	QLabel* sourceLabel = new QLabel{ "&Photograph Source:" };
	sourceLabel->setBuddy(this->photographSourceEdit);

	formLayout->addRow(nameLabel, this->nameEdit);
	formLayout->addRow(sizeLabel, this->sizeEdit);
	formLayout->addRow(priceLabel, this->priceEdit);
	formLayout->addRow(sourceLabel, this->photographSourceEdit);

	administratorLayout->addLayout(formLayout);

	this->addCoatButton = new QPushButton{ "Add Coat" };
	this->deleteCoatButton = new QPushButton{ "Delete Coat" };
	this->updateCoatButton = new QPushButton{ "Update Coat" };
	this->listButton = new QPushButton{ "List Coats" };

	buttons->addWidget(this->addCoatButton, 0, 0);
	buttons->addWidget(this->deleteCoatButton, 0, 1);
	buttons->addWidget(this->updateCoatButton, 0, 2);
	buttons->addWidget(this->listButton, 2, 0, 1, 3);
	
	administratorLayout->addLayout(buttons);

	QGridLayout* undoRedoButtons = new QGridLayout{};

	this->undoButton = new QPushButton{ "Undo" };
	this->redoButton = new QPushButton{ "Redo" };
	this->exitAdministratorMode = new QPushButton{ "Exit" };

	undoRedoButtons->addWidget(this->undoButton, 0, 1);
	undoRedoButtons->addWidget(this->redoButton, 0, 2);

	administratorLayout->addLayout(undoRedoButtons);

	administratorLayout->addWidget(this->exitAdministratorMode);
}

void GUI::initializeUserGUI()
{
	QVBoxLayout* userLayout = new QVBoxLayout{ this->userLayout };

	this->userList = new QListWidget{};

	this->nextCoatButton = new QPushButton{ "Next" };
	this->openUserCoatsButton = new QPushButton{ "Open user coats file" };
	this->exitButton = new QPushButton{ "Exit" };
	this->filterCoatsButton = new QPushButton{ "Filter coats" };
	this->undoUserButton = new QPushButton{ "Undo" };
	this->redoUserButton = new QPushButton{ "Redo" };

	QGridLayout* buttons = new QGridLayout{};

	buttons->addWidget(this->nextCoatButton, 0, 0);
	buttons->addWidget(this->openUserCoatsButton, 0, 1);
	buttons->addWidget(this->undoUserButton, 1, 0);
	buttons->addWidget(this->redoUserButton, 1, 1);
	buttons->addWidget(this->filterCoatsButton, 2, 0, 1, 2);
	buttons->addWidget(this->exitButton, 3, 0, 1, 2);

	userLayout->addWidget(this->userList);

	QFormLayout* formLayout = new QFormLayout{};

	QLabel* userCoatNameLabel = new QLabel{ "&Name: " };
	this->userCoatEdit = new QLineEdit{};
	userCoatNameLabel->setBuddy(this->userCoatEdit);
	formLayout->addRow(userCoatNameLabel, this->userCoatEdit);

	QLabel* userCoatSizeLabel = new QLabel{ "&Size" };
	this->userCoatSizeEdit = new QLineEdit{};
	userCoatSizeLabel->setBuddy(this->userCoatSizeEdit);
	formLayout->addRow(userCoatSizeLabel, this->userCoatSizeEdit);

	QLabel* userCoatPriceLabel = new QLabel{ "&Price" };
	this->userCoatPriceEdit = new QLineEdit{};
	userCoatPriceLabel->setBuddy(this->userCoatPriceEdit);
	formLayout->addRow(userCoatPriceLabel, this->userCoatPriceEdit);

	userLayout->addLayout(formLayout);

	this->saveToMyListButton = new QPushButton{ "Save " };

	userLayout->addWidget(this->saveToMyListButton);

	userLayout->addLayout(buttons);
}

void GUI::initializeBarChart()
{
	BarChart* chart = new BarChart{this->coatService.listCoats()};
	chart->show();
}

void GUI::initializeConnections()
{
	QObject::connect(this->addCoatButton, &QPushButton::clicked, this, [this]() {this->storeCoat(); });

	QObject::connect(this->listButton, &QPushButton::clicked, this, [this]() {this->listCoats(); });
	
	QObject::connect(this->exitButton, &QPushButton::clicked, this, [this]() {close(); });

	QObject::connect(this->exitAdministratorMode, &QPushButton::clicked, this, [this]() {close(); });
	
	QObject::connect(this->coatsList, &QListWidget::itemSelectionChanged, this, [this]() {this->listItemSelected(); });
	
	QObject::connect(this->deleteCoatButton, &QPushButton::clicked, this, [this]() {this->deleteCoat(); });
	
	QObject::connect(this->updateCoatButton, &QPushButton::clicked, this, [this]() {this->updateCoat(); });
	
	QObject::connect(this->filterCoatsButton, &QPushButton::clicked, this, [this]() {this->filterCoats(); });
	
	QObject::connect(this->undoButton, &QPushButton::clicked, this, [this]() {this->undo(); });
	
	QObject::connect(this->redoButton, &QPushButton::clicked, this, [this]() {this->redo(); });
	
	QObject::connect(this->nextCoatButton, &QPushButton::clicked, this, [this]() {this->nextCoat(); });
	
	QObject::connect(this->userList, &QListWidget::itemSelectionChanged, this, [this]() {this->listItemSelectedUserList(); });

	QObject::connect(this->openUserCoatsButton, &QPushButton::clicked, this, [this]() {this->openUserList(); });
	
	QObject::connect(this->saveToMyListButton, &QPushButton::clicked, this, [this]() {this->saveCoatToUserList(); });
	
	QObject::connect(this->toAdministratorMenu, &QAction::triggered, this, [this]() {
		this->stackedWidgets->setCurrentIndex(AdministratorMenu);
		this->listCoats();
		});

	QObject::connect(this->toUserMenu, &QAction::triggered, this, [this]() {
		this->stackedWidgets->setCurrentIndex(UserMenu);
		this->coatService.setCoatsIterator();
		if (this->userList->count() > 0)
			this->userList->clear();

		this->userCoatEdit->setText(QString::fromStdString(""));
		this->userCoatSizeEdit->setText(QString::fromStdString(""));
		this->userCoatPriceEdit->setText(QString::fromStdString(""));
		});

	QObject::connect(this->toTableView, &QAction::triggered, this, [this]() {
		//this->stackedWidgets->setCurrentIndex(TableView);
		this->userTableViewWidget->show();
		});

	QKeySequence undoKey{ Qt::CTRL + Qt::Key_Z };
	QShortcut* undoShortcut = new QShortcut{ undoKey, this};

	QKeySequence redoKey{ Qt::CTRL + Qt::Key_Y };
	QShortcut* redoShortcut = new QShortcut{ redoKey, this };

	QObject::connect(undoShortcut, &QShortcut::activated, this, [this]() {this->undo(); });
	QObject::connect(redoShortcut, &QShortcut::activated, this, [this]() {this->redo(); });

	QObject::connect(this->undoUserButton, &QPushButton::clicked, this, [this]() {this->userUndo(); });

	QObject::connect(this->redoUserButton, &QPushButton::clicked, this, [this]() {this->userRedo(); });
}

void GUI::readSettings()
{
	std::ifstream fileOut{ "settings.txt" };
	std::string coats, userCoats;
	std::getline(fileOut, coats, '=');
	std::getline(fileOut, coats);

	std::getline(fileOut, userCoats, '=');
	std::getline(fileOut, userCoats);

	this->coatService.setPath(coats, userCoats);
}

int GUI::getSelectedIndex(QListWidget* list)
{
	if (list->count() == 0)
		return -1;

	QModelIndexList index = list->selectionModel()->selectedIndexes();

	if (index.size() == 0)
	{
		this->nameEdit->clear();
		this->sizeEdit->clear();
		this->priceEdit->clear();
		this->photographSourceEdit->clear();
		return -1;
	}
	int integerIndex = index.at(0).row();
	return integerIndex;
}

void GUI::listItemSelected()
{
	int index = this->getSelectedIndex(this->coatsList);
	             
	if (index == -1 || index >= this->coatService.getRepositoryLength())
		return;

	TrenchCoat coat = this->coatService.getCoatFromRepository(index);

	this->nameEdit->setText(QString::fromStdString(coat.getName()));
	this->sizeEdit->setText(QString::fromStdString(coat.getSize()));
	this->priceEdit->setText(QString::fromStdString(std::to_string(coat.getPrice())));
	this->photographSourceEdit->setText(QString::fromStdString(coat.getPhotographSource()));

}

void GUI::listItemSelectedUserList()
{
	auto selectedCoat = this->userList->currentItem();

	std::vector<std::string> coatFields = tokenize(selectedCoat->text().toStdString(), ' ');

	std::string name = coatFields[0];
	std::string size = coatFields[1];
	std::string price = coatFields[2];

	this->userCoatEdit->setText(QString::fromStdString(name));
	this->userCoatSizeEdit->setText(QString::fromStdString(size));
	this->userCoatPriceEdit->setText(QString::fromStdString(price));
}

void GUI::storeCoat()
{	
	std::string name = this->nameEdit->displayText().toStdString();
	std::string size = this->sizeEdit->displayText().toStdString();
	std::string price = this->priceEdit->displayText().toStdString();
	std::string source = this->photographSourceEdit->displayText().toStdString();
	
	try
	{
		this->coatService.storeCoatService(name, size, source, price);
		QMessageBox::information(this, "Success", "Coat added successfully");
		this->listCoats();
	}
	catch (Exceptions & exception)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(exception.what()));
	}
}

void GUI::listCoats()
{
	if(this->coatsList->count() > 0)
		this->coatsList->clear();

	for (auto& coat : this->coatService.listCoats())
	{
		QString itemInList = QString::fromStdString(coat.to_string());
		QListWidgetItem* item = new QListWidgetItem{ itemInList };
		this->coatsList->addItem(item);
	}
}

void GUI::deleteCoat()
{
	std::string name = this->nameEdit->text().toStdString();
	try
	{
		this->userTableViewWidget->beginRemoveRow();
		int initialSize = this->coatService.getUserRepositoryLength();
		this->coatService.deleteCoatService(name);
		int finalSize = this->coatService.getUserRepositoryLength();

		if(finalSize < initialSize)
			this->userTableViewWidget->endRemoveRow();
		QMessageBox::information(this, "Success", "Coat deleted successfully");
		this->listCoats();
	}
	catch (Exceptions & exception)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(exception.what()));
	}
}

void GUI::updateCoat()
{
	std::string name = this->nameEdit->displayText().toStdString();
	std::string size = this->sizeEdit->displayText().toStdString();
	std::string price = this->priceEdit->displayText().toStdString();
	std::string source = this->photographSourceEdit->displayText().toStdString();

	try
	{
		this->coatService.updateCoatService(name, size, source, price);
		QMessageBox::information(this, "Success", "Coat updated successfully");
		this->listCoats();
	}
	catch (Exceptions & exception)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(exception.what()));
	}
}

void GUI::filterCoats()
{
	std::string size = this->userCoatSizeEdit->displayText().toStdString();
	std::string price = this->userCoatPriceEdit->displayText().toStdString();
	
	try
	{
		std::vector<TrenchCoat> filteredCoats = this->coatService.listFilteredCoats(size, price);
		if (this->userList->count() > 0)
			this->userList->clear();

		for (auto& coat : filteredCoats)
		{
			QString itemInList = QString::fromStdString(coat.to_string());
			QListWidgetItem* item = new QListWidgetItem{ itemInList };
			this->userList->addItem(item);
		}
	}
	catch (Exceptions & exception)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(exception.what()));
	}
}

void GUI::undo()
{
	try
	{
		this->coatService.undo();
		QMessageBox::information(this, "Success", "Successful undo");
		this->listCoats();
	}
	catch (Exceptions& exception)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(exception.what()));
	}
}

void GUI::redo()
{
	try
	{
		this->coatService.redo();
		QMessageBox::information(this, "Success", "Successful redo");
		this->listCoats();
	}
	catch (Exceptions& exception)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(exception.what()));
	}
}

void GUI::userUndo()
{
	try
	{
		this->userTableViewWidget->beginRemoveRow();
		int initialSize = this->coatService.getUserRepositoryLength();
		this->coatService.undoUser();
		int finalSize = this->coatService.getUserRepositoryLength();
		
		if (finalSize < initialSize)
			this->userTableViewWidget->endRemoveRow();

		QMessageBox::information(this, "Success", "Successful undo");
	}
	catch (Exceptions & exception)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(exception.what()));
	}
}

void GUI::userRedo()
{
	try
	{
		this->userTableViewWidget->beginAddRow();
		this->coatService.redoUser();
		this->userTableViewWidget->endAddRow();
		QMessageBox::information(this, "Success", "Successful redo");
	}
	catch (Exceptions & exception)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(exception.what()));
	}
}

void GUI::saveCoatToUserList()
{
	if (this->userCoatEdit->text().size() == 0)
	{
		QMessageBox::warning(this, "Warning", "Select a coat");
		return;
	}

	std::string name = this->userCoatEdit->text().toStdString();

	try
	{
		this->userTableViewWidget->beginAddRow();
		this->coatService.saveTrenchCoatToUserList(name);
		this->userTableViewWidget->endAddRow();
		QMessageBox::information(this, "Succes", "Coat saved to user list");
	}
	catch (Exceptions & exception)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(exception.what()));
	}
}

void GUI::nextCoat()
{
	int i = this->userList->count();
	if (this->userList->count() > 0)
		this->userList->clear();
	try
	{	
	TrenchCoat trenchCoat = this->coatService.getNextCoatFromIterator();
	std::string coat = trenchCoat.to_string();

	QString itemInList = QString::fromStdString(coat);
	QListWidgetItem* item = new QListWidgetItem{ itemInList };
	this->userList->addItem(item);

	this->userCoatEdit->setText(QString::fromStdString(trenchCoat.getName()));
	this->userCoatSizeEdit->setText(QString::fromStdString(trenchCoat.getSize()));
	this->userCoatPriceEdit->setText(QString::fromStdString(std::to_string(trenchCoat.getPrice())));

	}
	catch (Exceptions & exception)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(exception.what()));
	}

}

void GUI::openUserList()
{
	this->coatService.openUserFile();
}
