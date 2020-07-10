#include "GUI.h"

GUI::GUI(Service& srv, const std::string name,QWidget *parent)
    :srv{ srv }, name{ name }, QWidget(parent)
{
    ui.setupUi(this);
    this->srv.addObserver(this);
    this->setWindowTitle(QString::fromStdString(this->name));
    this->loadQuestions();

    QObject::connect(ui.addButton, &QPushButton::clicked, this, [this]() {this->addQuestion(); });

    QObject::connect(ui.questionsList, &QListWidget::itemSelectionChanged, this, [this]() {this->loadAnswers(); });

    QObject::connect(ui.answerButtonQ, &QPushButton::clicked, this, [this]() {this->addAnswer(); });
}

void GUI::loadQuestions()
{
    if (ui.questionsList->count() > 0)
    {
        ui.questionsList->blockSignals(true);
        ui.questionsList->clear();
        ui.questionsList->blockSignals(false);
    }
    for (auto& q : this->srv.getSortedQuestions())
    {
        QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(q.to_string(' ')) };
        ui.questionsList->addItem(item);
    }
}

void GUI::addQuestion()
{
    std::string desc = ui.descriptionEdit->text().toStdString();
    try
    {
        this->srv.addQuestion(desc, this->name);
    }
    catch (MyException & exc)
    {
        QMessageBox::warning(this, "Warning", QString::fromStdString(exc.what()));
    }
}

void GUI::loadAnswers()
{

    if (ui.answersList->count() > 0)
        ui.answersList->clear();
    std::string line = ui.questionsList->selectedItems()[0]->text().toStdString();
    int id = stoi(tokenize(line, ' ')[0]);

    std::vector<Answer> answers = this->srv.getAnswersForQ(id);

    for (Answer& a : answers)
    {
        QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(std::to_string(a.getId()) + ' ' + a.getName() + ' ' + a.getText() + ' ' + std::to_string(a.getVotes())) };
        if (a.getName() == this->name)
            item->setBackgroundColor(Qt::yellow);
        ui.answersList->addItem(item);
    }

}

void GUI::addAnswer()
{
    if (ui.questionsList->selectedItems().size() == 0)
        return;
    std::string line = ui.questionsList->selectedItems()[0]->text().toStdString();
    int id = stoi(tokenize(line,' ')[0]);

    line = ui.descriptionEdit->text().toStdString();

    try
    {
        this->srv.addAnswer(line, this->name, id);
    }
    catch (MyException & exc)
    {
        QMessageBox::warning(this, "Warning", QString::fromStdString(exc.what()));
    }
}
