#include "ParticipantWindow.h"

ParticipantWindow::ParticipantWindow(Service& service, const std::string& name, QWidget *parent)
	:srv{ service }, name{ name }, QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromStdString(this->name));
	this->loadData();
	QObject::connect(ui.answerButton, &QPushButton::clicked, this, [this]() {this->answer(); });
}

ParticipantWindow::~ParticipantWindow()
{
}

void ParticipantWindow::loadData()
{
	if (ui.questionList->count() > 0)
		ui.questionList->clear();
	std::vector<Question> questions = this->srv.getQuestions();
	
	std::sort(questions.begin(), questions.end(), [](Question& q1, Question& q2) {return q1.getScore() > q2.getScore(); });

	for (Question& q : questions)
	{
		QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(std::to_string(q.getId()) + ',' + q.getText() + ',' + std::to_string(q.getScore())) };
		auto it = std::find(this->answeredQuestions.begin(), this->answeredQuestions.end(), q.getId());
		if (it != this->answeredQuestions.end())
			item->setBackgroundColor(Qt::green);
		
		ui.questionList->addItem(item);
	}
}

void ParticipantWindow::answer()
{
	if (ui.questionList->selectedItems().size() == 0)
	{
		QMessageBox::warning(this, "Warning", "Select a message");
		return;
	}

	std::vector<std::string> info = tokenize(ui.questionList->selectedItems()[0]->text().toStdString(), ',');
	int id = stoi(info[0]);
	int score = stoi(info[2]);
	std::string answer = ui.answerEdit->text().toStdString();
	if (this->srv.correctAnswer(id, answer)==true)
	{
		auto it = std::find(this->answeredQuestions.begin(), this->answeredQuestions.end(), id);
		if (it != this->answeredQuestions.end())
		{
			return;
		}

		this->answeredQuestions.push_back(id);
		this->srv.setScore(this->name, score);
		ui.scoreLabel->setText("Score: " + QString::number(this->srv.getScore(this->name)));
		this->loadData();
	}
	else
		QMessageBox::warning(this, "Warning", "Bad answer");
}
