/********************************************************************************
** Form generated from reading UI file 'DialogGenesListWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGGENESLISTWIDGET_H
#define UI_DIALOGGENESLISTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogGenesWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QListWidget *listWidget;

    void setupUi(QDialog *DialogGenesWidget)
    {
        if (DialogGenesWidget->objectName().isEmpty())
            DialogGenesWidget->setObjectName(QString::fromUtf8("DialogGenesWidget"));
        DialogGenesWidget->resize(347, 405);
        horizontalLayout = new QHBoxLayout(DialogGenesWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        listWidget = new QListWidget(DialogGenesWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        horizontalLayout->addWidget(listWidget);


        retranslateUi(DialogGenesWidget);

        QMetaObject::connectSlotsByName(DialogGenesWidget);
    } // setupUi

    void retranslateUi(QDialog *DialogGenesWidget)
    {
        DialogGenesWidget->setWindowTitle(QCoreApplication::translate("DialogGenesWidget", "Genes List Widget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogGenesWidget: public Ui_DialogGenesWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGGENESLISTWIDGET_H
