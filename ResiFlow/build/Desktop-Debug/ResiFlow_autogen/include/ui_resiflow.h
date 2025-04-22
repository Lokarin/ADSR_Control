/********************************************************************************
** Form generated from reading UI file 'resiflow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESIFLOW_H
#define UI_RESIFLOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ResiFlow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ResiFlow)
    {
        if (ResiFlow->objectName().isEmpty())
            ResiFlow->setObjectName("ResiFlow");
        ResiFlow->resize(800, 600);
        centralwidget = new QWidget(ResiFlow);
        centralwidget->setObjectName("centralwidget");
        ResiFlow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ResiFlow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 23));
        ResiFlow->setMenuBar(menubar);
        statusbar = new QStatusBar(ResiFlow);
        statusbar->setObjectName("statusbar");
        ResiFlow->setStatusBar(statusbar);

        retranslateUi(ResiFlow);

        QMetaObject::connectSlotsByName(ResiFlow);
    } // setupUi

    void retranslateUi(QMainWindow *ResiFlow)
    {
        ResiFlow->setWindowTitle(QCoreApplication::translate("ResiFlow", "ResiFlow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ResiFlow: public Ui_ResiFlow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESIFLOW_H
