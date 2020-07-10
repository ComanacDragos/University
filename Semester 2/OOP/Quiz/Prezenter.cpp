#include "Prezenter.h"

Prezenter::Prezenter(Service& srv,QWidget *parent)
    :srv{ srv }, QWidget(parent)
{
    ui.setupUi(this);
	this->listQuestions();
	this->setWindowTitle("Presenter");

	QObject::connect(ui.pushButton, &QPushButton::clicked, this, [this] {this->addQuestion(); });

}

void Prezenter::listQuestions()
{
	if (ui.listWidget->count() > 0)
		ui.listWidget->clear();
	std::vector<Question> questions = srv.getQuestions();

	std::sort(questions.begin(), questions.end(), [](Question& q1, Question& q2) {return q1.getId() < q2.getId(); });

	for (Question& q : questions)
	{
		QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(q.to_string(' '))};
		ui.listWidget->addItem(item);
	}
}

void Prezenter::addQuestion()
{
	int id = stoi(ui.idEdit->text().toStdString());
	std::string text = ui.textEdit->text().toStdString();
	std::string answer = ui.answerEdit->text().toStdString();
	int score = stoi(ui.scoreEdit->text().toStdString());
	try
	{
		this->srv.addQuestion(id, text, answer, score);
		this->listQuestions();
	}
	catch (Exceptions exc)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(exc.what()));
	}

}


