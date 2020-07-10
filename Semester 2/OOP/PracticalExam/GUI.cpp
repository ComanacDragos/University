#include "GUI.h"

GUI::GUI(Service& srv, Astronomer a,TableModel* model, QWidget *parent)
    :srv{ srv }, astronomer{ a }, model{ model }, QWidget(parent)
{
    ui.setupUi(this);
    this->srv.addObserver(this);

    ui.starsView->setModel(this->model);
    this->setWindowTitle(QString::fromStdString(this->astronomer.getName()));

    ui.starsView->setSelectionBehavior(QAbstractItemView::SelectRows);
    
    this->filterModel = new FilterModel{ this->srv, this->astronomer.getConstelation() };
    this->filterModel->setSourceModel(this->model);
    this->allModel = this->model;

    QObject::connect(ui.addButton, &QPushButton::clicked, this, [this]() {this->addStar(); });

    QObject::connect(ui.searchEdit, &QLineEdit::textChanged, this, [this]() {this->loadStars(); });

    QObject::connect(ui.viewButton, &QPushButton::clicked, this, [this]() {this->viewStar(); });

    QObject::connect(ui.checkBox, &QCheckBox::stateChanged, this, [this]() {this->checkBox(); });
    
}

void GUI::loadStars()
{

    if (ui.starList->count() > 0)
        ui.starList->clear();

    std::string name = ui.searchEdit->text().toStdString();
    if (name.size() == 0)
        return;

    std::vector<Star> stars = this->srv.getStarByName(name);
    if (stars.size() == 0)
        return;


    for (Star& s : stars)
    {
        QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(s.to_string(' ')) };
        ui.starList->addItem(item);
    }
}

void GUI::addStar()
{
    std::string name = ui.nameEdit->text().toStdString();
    int RA = ui.RAEdit->text().toInt();
    int Desc = ui.decEdit->text().toInt();
    int diameter = ui.diameterEdit->text().toInt();

    try
    {
        this->model->beginAddRow();
        this->srv.addStar(name, this->astronomer.getConstelation(), RA, Desc, diameter);
        this->model->endAddRow();
    }
    catch (Exceptions & exc)
    {
        QMessageBox::warning(this, "Warning", QString::fromStdString(exc.what()));
    }
}

void GUI::viewStar()
{
    if (ui.starsView->selectionModel()->selectedIndexes().size() == 0)
        return;

    std::string name = ui.starsView->selectionModel()->selectedIndexes()[0].data().toString().toStdString();

    Painter* painter = new Painter{ this->srv, name };
    painter->show();
}

void GUI::checkBox()
{
    if (ui.checkBox->isChecked())
    {
        this->filterModel = new FilterModel{ this->srv, this->astronomer.getConstelation() };
        this->filterModel->setSourceModel(this->model);

        ui.starsView->setModel(this->filterModel);
    }
    else
    {
        ui.starsView->setModel(this->model);
    }
}
