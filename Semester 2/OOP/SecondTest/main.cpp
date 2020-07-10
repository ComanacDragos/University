#include "GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    Repo repo;
    Service srv{ repo };
    GUI w{ srv };
    w.show();

    QListWidget* list = new QListWidget{};

    QString itemInList = QString::fromStdString("asd");
    QListWidgetItem* item = new QListWidgetItem{ itemInList };
    
    item->setBackgroundColor(Qt::red);
    
    list->addItem(item);


    return a.exec();
}
