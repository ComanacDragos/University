#include "GUI.h"

GUI::GUI(Service& srv, QWidget *parent)
    :srv{ srv },QWidget(parent)
{
    ui.setupUi(this);
    this->listTasks();
    QObject::connect(ui.listButton, &QPushButton::clicked, this, [this]() {this->listTasks(); });
    QObject::connect(ui.filterButton, &QPushButton::clicked, this, [this]() {this->duration(); });
}

void GUI::listTasks()
{
    if (ui.taskList->count() > 0)
        ui.taskList->clear();
    for (Task& task : this->srv.getTasks())
    {
        QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(task.to_string()) };
        if (task.getPriority() == 1)
        {
            QFont f;
            f.setBold(1);
            item->setFont(f);
        }
        ui.taskList->addItem(item);
    }
}

void GUI::duration()
{
    int priority = stoi(ui.priorityEdit->text().toStdString());
    ui.durationEdit->setText(QString::fromStdString(std::to_string(this->srv.totalTime(priority))));
}
