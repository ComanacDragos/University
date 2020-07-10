#include "GUI.h"

GUI::GUI(Service& srv, Programmer programmer, QWidget *parent)
    :srv{ srv }, programmer{ programmer }, QWidget(parent)
{
    ui.setupUi(this);
    this->srv.addObserver(this);
    this->setWindowTitle(QString::fromStdString(this->programmer.getName()));
    this->loadData();

    QObject::connect(ui.addButton, &QPushButton::clicked, this, [this]() {this->addTask(); });

    QObject::connect(ui.removeTask, &QPushButton::clicked, this, [this]() {this->removeTask(); });

    QObject::connect(ui.startButton, &QPushButton::clicked, this, [this]() {this->startTask(); });

    QObject::connect(ui.doneButton, &QPushButton::clicked, this, [this]() {this->closeTask(); });
}

void GUI::loadData()
{
    if (ui.tasksList->count() > 0)
        ui.tasksList->clear();
    
    std::vector<Task> tasks = this->srv.getTasks();
    std::sort(tasks.begin(), tasks.end(), [](Task& t1, Task& t2) {return t1.getStatus() < t2.getStatus(); });

    for (Task& t : tasks)
    {
        std::string line = t.getDesc() + ' ' + t.getStatus();
        if (t.getStatus() != "open")
            line += ' ' + this->srv.getProgrammer(t.getId()).getName();
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(line));
        ui.tasksList->addItem(item);
    }
}

void GUI::addTask()
{
    std::string desc = ui.descEdit->text().toStdString();
    this->srv.addTask(desc, "open");
}

void GUI::removeTask()
{
    if (ui.tasksList->selectedItems().size() == 0)
        return;
    std::string line = ui.tasksList->selectedItems()[0]->text().toStdString();
    this->srv.removeTask(tokenize(line, ' ')[0]);
}

void GUI::startTask()
{
    if (ui.tasksList->selectedItems().size() == 0)
        return;
    std::string line = ui.tasksList->selectedItems()[0]->text().toStdString();
    std::vector<std::string> tokens = tokenize(line, ' ');
    try
    {
        this->srv.startTask(tokens[0], tokens[1], this->programmer.getId());
    }
    catch (MyException & exc)
    {
        QMessageBox::warning(this, "Warning", QString::fromStdString(exc.what()));
    }
}

void GUI::closeTask()
{
    if (ui.tasksList->selectedItems().size() == 0)
        return;
    std::string line = ui.tasksList->selectedItems()[0]->text().toStdString();
    std::vector<std::string> tokens = tokenize(line, ' ');
    this->srv.closeTask(tokens[0], tokens[1], this->programmer.getId());
    
}
