#include "Search.h"

Search::Search(Service& srv,QWidget *parent)
	:srv{ srv }, QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle("Search");
	QObject::connect(ui.lineEdit, &QLineEdit::textChanged, this, [this]() {this->loadData(); });
}

Search::~Search()
{
}

void Search::loadData()
{
	std::string desc = ui.lineEdit->text().toStdString();
	if (desc.size() == 0)
		return;

	Question q = this->srv.bestMatching(desc);

	std::vector<Answer> answers = this->srv.getAnswersForQ(q.getId());

	std::sort(answers.begin(), answers.end(), [](Answer& a1, Answer& a2) {return a1.getVotes() > a2.getVotes(); });

	int n = answers.size();
	if (n > 3)
		n = 3;

	std::string info = q.to_string(' ')+'\n';
	for (int i = 0; i < n; i++)
	{
		info +="    " + answers[i].to_string(' ')+'\n';
	}
	ui.textEdit->setText(QString::fromStdString(info));
}
