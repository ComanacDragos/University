#include "SearchWindow.h"

SearchWindow::SearchWindow(Service& srv,QWidget *parent)
	:srv{ srv }, QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle("Search");
	QObject::connect(ui.searchEdit, &QLineEdit::textChanged, this, [this]() {this->loadQuestion(); });
	this->srv.addObserver(this);
}

SearchWindow::~SearchWindow()
{
}

void SearchWindow::loadQuestion()
{
	std::string text = ui.searchEdit->text().toStdString();
	if (text.size() == 0)
		return;

	if (ui.list->count() > 0)
		ui.list->clear();
	Question q = this->srv.searchQuestion(text);
	QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(q.to_string(' ')) };
	ui.list->addItem(item);

	std::vector<Answer> answers = this->srv.getAnswersToQ(q.getId());

	std::sort(answers.begin(), answers.end(), [](Answer& a1, Answer& a2) {return a1.getVotes() > a2.getVotes(); });

	int size = answers.size();
	if (size > 3)
		size = 3;
	for (int i = 0; i < size; i += 1)
	{
		QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString("	" +answers[i].to_string(' ')) };
		ui.list->addItem(item);
	}
}
