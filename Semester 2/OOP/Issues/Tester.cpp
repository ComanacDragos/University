#include "Tester.h"

Tester::Tester(Service& srv, User& user, QWidget* parent)
	:srv{ srv }, user{ user }, QWidget(parent)
{
	ui.setupUi(this);

	this->setWindowTitle(QString::fromStdString(this->user.getName() + ' ' + this->user.getType()));
	this->loadData();

	QObject::connect(ui.addButton, &QPushButton::clicked, this, [this]() {this->addIssue(); });
	QObject::connect(ui.deleteButton, &QPushButton::clicked, this, [this]() {this->removeIssue(); });

	this->srv.addObserver(this);
}

Tester::~Tester()
{
}

void Tester::loadData()
{
	if (ui.issueList->count() > 0)
		ui.issueList->clear();

	std::vector<Issue> issues = this->srv.getIssues();
	std::sort(issues.begin(), issues.end(), [](Issue& i1, Issue& i2) {
		if (i1.getStatus() < i2.getStatus())
			return true;
		else if (i1.getStatus() == i2.getStatus())
			return i1.getDescription() < i2.getDescription();
		return false;
		});

	for (Issue& i : issues)
	{
		QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(i.to_string(' ')) };
		ui.issueList->addItem(item);
	}
}

void Tester::update()
{
	this->loadData();
}

void Tester::addIssue()
{
	std::string description = ui.descriptionEdit->text().toStdString();
	try
	{
		this->srv.addIssue(description, "open", this->user.getName());
	}
	catch (MyException & exc)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(exc.what()));
	}
}
