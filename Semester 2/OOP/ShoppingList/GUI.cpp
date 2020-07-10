#include "GUI.h"

GUI::GUI(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    this->listItems();
    QObject::connect(ui.deleteButton, &QPushButton::clicked, this, [this]() {this->deleteItem(); });
    QObject::connect(ui.listButton, &QPushButton::clicked, this, [this]() {this->listItems(); });
    QObject::connect(ui.filterButton, &QPushButton::clicked, this, [this]() {this->filterItems(); });

}

void GUI::listItems()
{
    if (ui.itemsList->count() > 0)
        ui.itemsList->clear();

    for (Item& item : this->srv.getItems())
    {
        QListWidgetItem* widgetItem = new QListWidgetItem{ QString::fromStdString(item.to_string()) };
        ui.itemsList->addItem(widgetItem);
    }
}

void GUI::deleteItem()
{
    std::string name = ui.nameEdit->text().toStdString();
    try
    {
        this->srv.deleteItem(name);
        QMessageBox::information(this, "Success", "Item deleted successfully");
    }
    catch (std::exception & exc)
    {
        std::string s = exc.what();
        QMessageBox::warning(this, "Warning", QString::fromStdString(s));
    }
    this->listItems();
}

void GUI::filterItems()
{
    if (ui.itemsList->count() > 0)
        ui.itemsList->clear();

    for (Item& item : this->srv.filterItems(ui.categoryEdit->text().toStdString()))
    {
        QListWidgetItem* widgetItem = new QListWidgetItem{ QString::fromStdString(item.to_string()) };
        ui.itemsList->addItem(widgetItem);
    }

}
