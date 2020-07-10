#include "GUI.h"

GUI::GUI(Service& srv, Writer writer,TableModel* model,QWidget *parent)
    :srv{ srv }, writer{ writer }, model{ model }, QWidget(parent)
{
    ui.setupUi(this);
    this->srv.addObserver(this);
    this->setWindowTitle(QString::fromStdString(this->writer.getName()));
    ui.ideeasView->setModel(this->model);
    ui.ideeasView->resizeColumnsToContents();
    ui.ideeasView->verticalHeader()->hide();
   
    QObject::connect(ui.saveIdeaButton, &QPushButton::clicked, this, [this]() {this->addIdea(); });

    QObject::connect(ui.developButton, &QPushButton::clicked, this, [this]() {this->developIdeeas(); });

    QObject::connect(ui.savePlotButton, &QPushButton::clicked, this, [this]() {this->savePlot(); });
}

void GUI::addIdea()
{
    std::string desc = ui.descriptionEdit->text().toStdString();
    int act = ui.actEdit->text().toInt();

    try
    {
        this->model->beginAddRow();
        this->srv.addIdea(desc, "proposed", this->writer.getName(), act);
        this->model->endAddRow();
    }
    catch (MyException & exc)
    {
        QMessageBox::warning(this, "Warning", QString::fromStdString(exc.what()));
    }
}

void GUI::developIdeeas()
{
    for (Idea& idea : this->srv.getAcceptedIdeeas(this->writer.getName()))
    {
        QWidget* widget = new QWidget{};
        QTextEdit* edit = new QTextEdit{ QString::fromStdString(idea.getDesc()) };
        QVBoxLayout* ly = new QVBoxLayout{ widget };
        ly->addWidget(edit);

        QPushButton* save = new QPushButton{ "Save" };
        ly->addWidget(save);

        QLabel* label = new QLabel{ "File" };
        QLineEdit* fileEdit = new QLineEdit{};
        label->setBuddy(fileEdit);

        QFormLayout* form = new QFormLayout{};
        form->setWidget(0, QFormLayout::LabelRole, label);
        form->setWidget(0, QFormLayout::FieldRole, fileEdit);


        ly->addLayout(form);

        QObject::connect(save, &QPushButton::clicked, widget, [fileEdit, edit]()
            {
                std::string file = fileEdit->text().toStdString();
                std::ofstream fout{ file };
                std::string content = edit->toPlainText().toStdString();
                fout << content;
                fout.close();

            });

        widget->show();
    }
}

void GUI::savePlot()
{
    std::ofstream fout{ "plot.txt" };

    for (int i = 1; i <= 3; i += 1)
    {
        fout << "Act " << i << ':' << '\n';
        for (Idea& i : this->srv.getAllAcceptedIdeeasOnAct(i))
        {
            fout << i.getDesc() << " (" << i.getCreator() << ')' << '\n';
        }
    }
}
