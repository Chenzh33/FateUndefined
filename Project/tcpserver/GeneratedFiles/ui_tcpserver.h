/********************************************************************************
** Form generated from reading UI file 'tcpserver.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPSERVER_H
#define UI_TCPSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tcpserverClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *tcpserverClass)
    {
        if (tcpserverClass->objectName().isEmpty())
            tcpserverClass->setObjectName(QStringLiteral("tcpserverClass"));
        tcpserverClass->resize(600, 400);
        menuBar = new QMenuBar(tcpserverClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        tcpserverClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(tcpserverClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        tcpserverClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(tcpserverClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tcpserverClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(tcpserverClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        tcpserverClass->setStatusBar(statusBar);

        retranslateUi(tcpserverClass);

        QMetaObject::connectSlotsByName(tcpserverClass);
    } // setupUi

    void retranslateUi(QMainWindow *tcpserverClass)
    {
        tcpserverClass->setWindowTitle(QApplication::translate("tcpserverClass", "tcpserver", 0));
    } // retranslateUi

};

namespace Ui {
    class tcpserverClass: public Ui_tcpserverClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPSERVER_H
