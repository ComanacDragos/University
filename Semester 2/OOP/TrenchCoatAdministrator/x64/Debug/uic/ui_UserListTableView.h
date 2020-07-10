/********************************************************************************
** Form generated from reading UI file 'UserListTableView.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERLISTTABLEVIEW_H
#define UI_USERLISTTABLEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserListTableView
{
public:
    QHBoxLayout *horizontalLayout;
    QTableView *userTableView;

    void setupUi(QWidget *UserListTableView)
    {
        if (UserListTableView->objectName().isEmpty())
            UserListTableView->setObjectName(QString::fromUtf8("UserListTableView"));
        UserListTableView->resize(400, 300);
        horizontalLayout = new QHBoxLayout(UserListTableView);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        userTableView = new QTableView(UserListTableView);
        userTableView->setObjectName(QString::fromUtf8("userTableView"));

        horizontalLayout->addWidget(userTableView);


        retranslateUi(UserListTableView);

        QMetaObject::connectSlotsByName(UserListTableView);
    } // setupUi

    void retranslateUi(QWidget *UserListTableView)
    {
        UserListTableView->setWindowTitle(QCoreApplication::translate("UserListTableView", "UserListTableView", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserListTableView: public Ui_UserListTableView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERLISTTABLEVIEW_H
