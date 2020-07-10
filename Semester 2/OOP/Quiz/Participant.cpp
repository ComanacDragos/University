#include "Participant.h"

ParticipantGUI::ParticipantGUI(Service& srv, Participant p, QWidget *parent)
	:srv{ srv }, participant{ Participant{ p.getName(), p.getScore() } }, QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromStdString(this->participant.getName()));
	ui.scoreLabel->setText("Score : " + QString::fromStdString(std::to_string(this->participant.getScore())));
	this->listQuestions();
	
	QObject::connect(ui.answerButton, &QPushButton::clicked, this, [this]() {this->answer(); });
}


ParticipantGUI::~ParticipantGUI()
{
}

void ParticipantGUI::listQuestions()
{
	if (ui.listWidget->count() > 0)
		ui.listWidget->clear();
	std::vector<Question> questions = srv.getQuestions();

	std::sort(questions.begin(), questions.end(), [](Question& q1, Question& q2) {return q1.getScore() > q2.getScore(); });

	for (Question& q : questions)
	{
		QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(std::to_string(q.getId()) + " " + q.getText() + " " + std::to_string(q.getScore())) };
		auto it = std::find(this->answeredQuestions.begin(), answeredQuestions.end(), q.getId());
		if (it != this->answeredQuestions.end())
		{
			item->setBackground(QColor(Qt::green));
		}

		ui.listWidget->addItem(item);
 	}
}

void ParticipantGUI::update()
{
	this->listQuestions();
}

void ParticipantGUI::answer()
{
	std::string answer = ui.answerEdit->text().toStdString();

	if (ui.listWidget->selectedItems().size() == 0)
	{
		QMessageBox::warning(this, "Warning", "Select question");
		return;
	}
	
	std::string line = ui.listWidget->selectedItems()[0]->text().toStdString();
	
	int id = stoi(tokenize(line, ' ')[0]);

	Question q = this->srv.getQuestion(id);

	if (answer == q.getAnswer())
	{
		auto it = std::find(this->answeredQuestions.begin(), answeredQuestions.end(), id);
		if (it != this->answeredQuestions.end())
		{
			QMessageBox::warning(this, "Warning", "Already answered");
			return;
		}

		QBrush* brush = new QBrush{};
		brush->setColor(Qt::green);
		ui.listWidget->selectedItems()[0]->setBackground(QColor(Qt::green));
		int score = q.getScore() + this->participant.getScore();
		this->participant.setScore(score);

		ui.scoreLabel->setText("Score: " + QString::number(score));
		this->answeredQuestions.push_back(id);
	}
	else
	{
		QMessageBox::warning(this,"Warning", "Bad Answer!");
	}
}

