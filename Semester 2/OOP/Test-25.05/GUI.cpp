#include "GUI.h"

GUI::GUI(Service& srv, QWidget *parent)
    :srv{ srv }, QWidget(parent)
{
    ui.setupUi(this);
    this->list();
    QObject::connect(ui.showButton, &QPushButton::clicked, this, [this] {this->nrCars(); });
}

void GUI::list()
{
    if (ui.carsList->count() > 0)
        ui.carsList->clear();
    for (Car& car : this->srv.getCars())
    {
        QListWidgetItem* item = new QListWidgetItem{QString::fromStdString(car.to_string())};
        item->setTextColor(QString::fromStdString(car.getColor()));
        ui.carsList->addItem(item);
    }
}

void GUI::nrCars()
{
    std::string manufacturer = ui.manufacturerEdit->text().toStdString();
    int cars = this->srv.nrCars(manufacturer);
    ui.carsEdit->setText(QString::number(cars));

}
