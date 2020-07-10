#include "GUI.h"

GUI::GUI(Service& srv, QWidget *parent)
    :srv{ srv }, QWidget(parent)
{
    ui.setupUi(this);
    this->listFamilies();

    QObject::connect(ui.familyList, &QListWidget::itemClicked, this, [this]() {this->listVegetables(); });
    QObject::connect(ui.searchButton, &QPushButton::clicked, this, [this]() {this->vegetable(); });
}

void GUI::listFamilies()
{
    if (ui.familyList->count() > 0)
        ui.familyList->clear();
    for (auto& s : this->srv.getFamilies())
    {
        QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(s) };
        ui.familyList->addItem(item);
    }
}

void GUI::listVegetables()
{
    std::string family= ui.familyList->selectedItems()[0]->text().toStdString();
    std::vector<Vegetable> v = this->srv.getVegetablesFromFamily(family);
    
    if (ui.vegetablesList->count() > 0)
        ui.vegetablesList->clear();
    for (Vegetable& vegetable : v)
    {
        QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(vegetable.to_string()) };
        ui.vegetablesList->addItem(item);
    }
}

void GUI::vegetable()
{
    std::string name = ui.nameEdit->text().toStdString();
    Vegetable vegetable = srv.getVegetable(name);
    ui.partsEdit->setText(QString::fromStdString(vegetable.getParts()));

    if(ui.familyList->count()>0)
    {
        ui.familyList->clear();
     }
    for (auto& s : this->srv.getFamilies())
    {
        QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(s) };
        if (vegetable.getFamily() == s)
            item->setBackgroundColor(Qt::red);
        ui.familyList->addItem(item);
    }
}
