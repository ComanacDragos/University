#include "Presenter.h"

Presenter::Presenter(Service& service, QWidget *parent)
    :srv{ service }, QWidget(parent)
{
    ui.setupUi(this);
    this->loadData();
    QObject::connect(ui.addButton, &QPushButton::clicked, this, [this]() {this->addQuestion(); });
}

void Presenter::loadData()
{
    if (ui.questionList->count() > 0)
        ui.questionList->clear();
    std::vector<Question> questions = this->srv.getQuestions();
    std::sort(questions.begin(), questions.end(), [](Question& q1, Question& q2) {return q1.getId() < q2.getId(); });
    
    for (Question& q : questions)
    {
        QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(q.to_string()) };
        ui.questionList->addItem(item);
    }
}

void Presenter::addQuestion()
{
    if (ui.textEdit->text().size() == 0)
    {
        QMessageBox::warning(this, "Warning", "Text is empty");
        return;
    }
    int id = ui.idEdit->text().toInt();
    std::string text = ui.textEdit->text().toStdString();
    std::string answer = ui.answerEdit->text().toStdString();
    int score = ui.scoreEdit->text().toInt();
    Question q{ id, text, answer, score };
    try
    {
        this->srv.addQuestion(q);
    }
    catch (MyException exc)
    {
        QMessageBox::warning(this, "Warning", QString::fromStdString(exc.what()));
    }
    this->loadData();
}
