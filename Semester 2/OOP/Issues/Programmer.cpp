#include "Programmer.h"

Programmer::Programmer(Service& srv, User& user, QWidget* parent)
	:srv{ srv }, user{ user }, QWidget(parent)
{
	ui.setupUi(this);

	this->setWindowTitle(QString::fromStdString(this->user.getName() + ' ' + this->user.getType()));
	this->loadData();

	this->srv.addObserver(this);

	QObject::connect(ui.deleteButton, &QPushButton::clicked, this, [this]() {this->removeIssue(); });
	QObject::connect(ui.resolveButton, &QPushButton::clicked, this, [this]() {this->resolveIssue(); });
}

Programmer::~Programmer()
{
}

void Programmer::loadData()
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

void Programmer::update()
{
	this->loadData();
}

void Programmer::removeIssue()
{
	std::string line = ui.issueList->selectedItems()[0]->text().toStdString();
	this->srv.removeIssue(tokenize(line,' ')[0]);
}

void Programmer::resolveIssue()
{
	std::string line = ui.issueList->selectedItems()[0]->text().toStdString();
	this->srv.resolveIssue(tokenize(line, ' ')[0], this->user.getName());
}
