/********************************************************************************
** Form generated from reading UI file 'bidderwithdescription.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BIDDERWITHDESCRIPTION_H
#define UI_BIDDERWITHDESCRIPTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BidderWithDescription
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *labelDescription;
    QLabel *labelPrice;
    QHBoxLayout *horizontalLayout;
    QPushButton *add100Button;
    QPushButton *add1000Button;

    void setupUi(QWidget *BidderWithDescription)
    {
        if (BidderWithDescription->objectName().isEmpty())
            BidderWithDescription->setObjectName(QString::fromUtf8("BidderWithDescription"));
        BidderWithDescription->resize(470, 252);
        horizontalLayout_2 = new QHBoxLayout(BidderWithDescription);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labelDescription = new QLabel(BidderWithDescription);
        labelDescription->setObjectName(QString::fromUtf8("labelDescription"));
        QFont font;
        font.setPointSize(20);
        labelDescription->setFont(font);

        verticalLayout->addWidget(labelDescription);

        labelPrice = new QLabel(BidderWithDescription);
        labelPrice->setObjectName(QString::fromUtf8("labelPrice"));
        labelPrice->setFont(font);

        verticalLayout->addWidget(labelPrice);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        add100Button = new QPushButton(BidderWithDescription);
        add100Button->setObjectName(QString::fromUtf8("add100Button"));
        QFont font1;
        font1.setPointSize(18);
        add100Button->setFont(font1);

        horizontalLayout->addWidget(add100Button);

        add1000Button = new QPushButton(BidderWithDescription);
        add1000Button->setObjectName(QString::fromUtf8("add1000Button"));
        add1000Button->setFont(font1);

        horizontalLayout->addWidget(add1000Button);


        verticalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout_2);


        retranslateUi(BidderWithDescription);

        QMetaObject::connectSlotsByName(BidderWithDescription);
    } // setupUi

    void retranslateUi(QWidget *BidderWithDescription)
    {
        BidderWithDescription->setWindowTitle(QCoreApplication::translate("BidderWithDescription", "BidderWithDescription", nullptr));
        labelDescription->setText(QString());
        labelPrice->setText(QString());
        add100Button->setText(QCoreApplication::translate("BidderWithDescription", "Add 100", nullptr));
        add1000Button->setText(QCoreApplication::translate("BidderWithDescription", "Add 1000", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BidderWithDescription: public Ui_BidderWithDescription {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BIDDERWITHDESCRIPTION_H
