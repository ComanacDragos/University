#include "GUI.h"

GUI::GUI(Service& srv,QWidget *parent)
    :srv{ srv }, QWidget(parent)
{
    ui.setupUi(this);
    this->listBills();
    QObject::connect(ui.sortButton, &QPushButton::clicked, this, [this]() {
        this->srv.sort();
        this->listBills();
        });

    QObject::connect(ui.calculateTotalButton, &QPushButton::clicked, this, [this]() {
        std::string company = ui.companyEdit->text().toStdString();
        double total = this->srv.calculateTotal(company);
        ui.totalEdit->setText(QString::fromStdString(std::to_string(total)));
        });
}

void GUI::listBills()
{
    if (ui.billsList->count() > 0)
        ui.billsList->clear();
    for (Bill& b : this->srv.getBills())
    {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(b.to_string()));
        ui.billsList->addItem(item);
    }
}
