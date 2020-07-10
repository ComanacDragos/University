/********************************************************************************
** Form generated from reading UI file 'lecture9_demo_qt_designer.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LECTURE9_DEMO_QT_DESIGNER_H
#define UI_LECTURE9_DEMO_QT_DESIGNER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lecture9_demo_Qt_designerClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QFormLayout *formLayout;
    QLabel *nameLabel;
    QLineEdit *nameEdit;
    QLabel *emailLabel;
    QLineEdit *emailEdit;
    QLabel *genderLabel;
    QComboBox *genderComboBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *OKButton;
    QPushButton *newButton;
    QPushButton *CancelButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Lecture9_demo_Qt_designerClass)
    {
        if (Lecture9_demo_Qt_designerClass->objectName().isEmpty())
            Lecture9_demo_Qt_designerClass->setObjectName(QString::fromUtf8("Lecture9_demo_Qt_designerClass"));
        Lecture9_demo_Qt_designerClass->resize(552, 544);
        centralWidget = new QWidget(Lecture9_demo_Qt_designerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout->addWidget(listWidget);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        nameLabel = new QLabel(centralWidget);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, nameLabel);

        nameEdit = new QLineEdit(centralWidget);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, nameEdit);

        emailLabel = new QLabel(centralWidget);
        emailLabel->setObjectName(QString::fromUtf8("emailLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, emailLabel);

        emailEdit = new QLineEdit(centralWidget);
        emailEdit->setObjectName(QString::fromUtf8("emailEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, emailEdit);

        genderLabel = new QLabel(centralWidget);
        genderLabel->setObjectName(QString::fromUtf8("genderLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, genderLabel);

        genderComboBox = new QComboBox(centralWidget);
        genderComboBox->setObjectName(QString::fromUtf8("genderComboBox"));

        formLayout->setWidget(2, QFormLayout::FieldRole, genderComboBox);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        OKButton = new QPushButton(centralWidget);
        OKButton->setObjectName(QString::fromUtf8("OKButton"));

        horizontalLayout->addWidget(OKButton);

        newButton = new QPushButton(centralWidget);
        newButton->setObjectName(QString::fromUtf8("newButton"));
        QFont font;
        font.setPointSize(14);
        newButton->setFont(font);

        horizontalLayout->addWidget(newButton);

        CancelButton = new QPushButton(centralWidget);
        CancelButton->setObjectName(QString::fromUtf8("CancelButton"));

        horizontalLayout->addWidget(CancelButton);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        Lecture9_demo_Qt_designerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Lecture9_demo_Qt_designerClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 552, 21));
        Lecture9_demo_Qt_designerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Lecture9_demo_Qt_designerClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Lecture9_demo_Qt_designerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Lecture9_demo_Qt_designerClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Lecture9_demo_Qt_designerClass->setStatusBar(statusBar);

        retranslateUi(Lecture9_demo_Qt_designerClass);

        QMetaObject::connectSlotsByName(Lecture9_demo_Qt_designerClass);
    } // setupUi

    void retranslateUi(QMainWindow *Lecture9_demo_Qt_designerClass)
    {
        Lecture9_demo_Qt_designerClass->setWindowTitle(QCoreApplication::translate("Lecture9_demo_Qt_designerClass", "Lecture9_demo_Qt_designer", nullptr));
        nameLabel->setText(QCoreApplication::translate("Lecture9_demo_Qt_designerClass", "Name", nullptr));
        emailLabel->setText(QCoreApplication::translate("Lecture9_demo_Qt_designerClass", "Email", nullptr));
        genderLabel->setText(QCoreApplication::translate("Lecture9_demo_Qt_designerClass", "Gender", nullptr));
        OKButton->setText(QCoreApplication::translate("Lecture9_demo_Qt_designerClass", "OK", nullptr));
        newButton->setText(QCoreApplication::translate("Lecture9_demo_Qt_designerClass", "PushButton", nullptr));
        CancelButton->setText(QCoreApplication::translate("Lecture9_demo_Qt_designerClass", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Lecture9_demo_Qt_designerClass: public Ui_Lecture9_demo_Qt_designerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LECTURE9_DEMO_QT_DESIGNER_H
