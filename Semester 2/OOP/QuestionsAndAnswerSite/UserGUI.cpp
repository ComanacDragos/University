#include "UserGUI.h"

UserGUI::UserGUI(Service& srv, const std::string user, QWidget *parent)
    :srv{ srv }, user{ user }, QWidget(parent)
{
    ui.setupUi(this);

    this->setWindowTitle(QString::fromStdString(this->user));
    this->srv.addObserver(this);
    this->loadQuestions();

    QObject::connect(ui.searchButton, &QPushButton::clicked, this, [this]() {
        SearchWindow* window = new SearchWindow{ this->srv };
        window->show();
        });
    QObject::connect(ui.askButton, &QPushButton::clicked, this, [this] {this->addQuestion(); });

    QObject::connect(ui.answerButton, &QPushButton::clicked, this, [this] {this->addAnswer(); });

    QObject::connect(ui.questionList, &QListWidget::itemClicked, this, [this]() {this->loadAnswers(); });

    QObject::connect(ui.spinBox, &QSpinBox::textChanged, [this]() {
        //QListWidgetItem* item = ui.questionList->selectedItems()[0];
        this->setVotes();
        //item->setSelected(true);
        });

    QObject::connect(ui.answerList, &QListWidget::itemClicked, this, [this]() {this->setSpinBox(); });
}

void UserGUI::loadQuestions()
{
    if (ui.questionList->count() > 0)
        ui.questionList->clear();

    
    std::vector<std::pair<Question, int>>questions;
    for (Question& q : srv.getQuestions())
    {
        questions.push_back(std::make_pair(q, this->srv.getAnswersToQ(q.getId()).size()));
    }
    std::sort(questions.begin(), questions.end(), [](std::pair<Question, int>& q1, std::pair<Question, int>& q2) {return q1.second > q2.second; });

    for (auto& q : questions)
    {
        QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(q.first.to_string(' ')) };
        ui.questionList->addItem(item);
    }
}

void UserGUI::addQuestion()
{
    std::string desc = ui.questionEdit->text().toStdString();
    try
    {
        this->srv.addQuestion(desc, this->user);
    }
    catch (MyException & exc)
    {
        QMessageBox::warning(this, "Warning", QString::fromStdString(exc.what()));
    }
}

void UserGUI::addAnswer()
{
    if (ui.questionList->selectedItems().size() == 0)
        return;
    std::vector<std::string> tokens = tokenize(ui.questionList->selectedItems()[0]->text().toStdString(), ' ');
    if (tokens.size() == 0)
        return;

    int id = stoi(tokens[0]);
    std::string text = ui.answerEdit->text().toStdString();
    try
    {
        this->srv.addAnswer(id, text, this->user);
    }
    catch (MyException & exc)
    {
        QMessageBox::warning(this, "Warning", QString::fromStdString(exc.what()));
    }

}

void UserGUI::setVotes()
{
    if (ui.answerList->selectedItems().size() == 0)
        return;
    std::string line = ui.answerList->selectedItems()[0]->text().toStdString();
    std::vector<std::string> tokens = tokenize(line, ' ');
    if (this->user == tokens[1])
        return;

    this->srv.setVotes(stoi(tokens[0]), ui.spinBox->value());
}

void UserGUI::setSpinBox()
{
    if (ui.answerList->selectedItems().size() == 0)
        return;
    std::string line = ui.answerList->selectedItems()[0]->text().toStdString();
    std::vector<std::string> tokens = tokenize(line, ' ');
    
    ui.spinBox->setValue(stoi(tokens[3]));
}

void UserGUI::loadAnswers()
{
    std::vector<std::string> tokens;
    if (ui.questionList->selectedItems().size() != 0)
        tokens = tokenize(ui.questionList->selectedItems()[0]->text().toStdString(), ' ');

    if (tokens.size() == 0 && this->idSelectedQ == -1)
        return;
    if (ui.answerList->count() > 0)
        ui.answerList->clear();
    int id;

    if(tokens.size()!=0)
    {
        id = stoi(tokens[0]);
        this->idSelectedQ = id;
    }
    std::vector<Answer> answers = this->srv.getAnswersToQ(this->idSelectedQ);

    for (Answer& a : answers)
    {
        QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(a.to_string(' ')) };
        if (a.getUser() == this->user)
            item->setBackgroundColor(Qt::yellow);
        ui.answerList->addItem(item);
    }
}
