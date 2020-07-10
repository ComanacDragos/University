/********************************************************************************
** Form generated from reading UI file 'bidderwithphoto.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BIDDERWITHPHOTO_H
#define UI_BIDDERWITHPHOTO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BidderWithPhoto
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *photoLabel;
    QLabel *priceLabel;
    QPushButton *add2000Button;

    void setupUi(QWidget *BidderWithPhoto)
    {
        if (BidderWithPhoto->objectName().isEmpty())
            BidderWithPhoto->setObjectName(QString::fromUtf8("BidderWithPhoto"));
        BidderWithPhoto->resize(439, 415);
        verticalLayout_2 = new QVBoxLayout(BidderWithPhoto);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        photoLabel = new QLabel(BidderWithPhoto);
        photoLabel->setObjectName(QString::fromUtf8("photoLabel"));
        QFont font;
        font.setPointSize(20);
        photoLabel->setFont(font);

        verticalLayout->addWidget(photoLabel);

        priceLabel = new QLabel(BidderWithPhoto);
        priceLabel->setObjectName(QString::fromUtf8("priceLabel"));
        priceLabel->setFont(font);

        verticalLayout->addWidget(priceLabel);


        verticalLayout_2->addLayout(verticalLayout);

        add2000Button = new QPushButton(BidderWithPhoto);
        add2000Button->setObjectName(QString::fromUtf8("add2000Button"));
        QFont font1;
        font1.setPointSize(18);
        add2000Button->setFont(font1);

        verticalLayout_2->addWidget(add2000Button);


        retranslateUi(BidderWithPhoto);

        QMetaObject::connectSlotsByName(BidderWithPhoto);
    } // setupUi

    void retranslateUi(QWidget *BidderWithPhoto)
    {
        BidderWithPhoto->setWindowTitle(QCoreApplication::translate("BidderWithPhoto", "BidderWithPhoto", nullptr));
        photoLabel->setText(QString());
        priceLabel->setText(QString());
        add2000Button->setText(QCoreApplication::translate("BidderWithPhoto", "Add 2000", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BidderWithPhoto: public Ui_BidderWithPhoto {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BIDDERWITHPHOTO_H
