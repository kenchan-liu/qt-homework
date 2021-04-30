/********************************************************************************
** Form generated from reading UI file 'othello.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OTHELLO_H
#define UI_OTHELLO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_othello
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QRadioButton *aim;
    QRadioButton *hmm;
    QLineEdit *lineEdit;
    QLabel *label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *othello)
    {
        if (othello->objectName().isEmpty())
            othello->setObjectName(QStringLiteral("othello"));
        othello->resize(846, 591);
        centralWidget = new QWidget(othello);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(450, 80, 61, 51));
        aim = new QRadioButton(centralWidget);
        aim->setObjectName(QStringLiteral("aim"));
        aim->setGeometry(QRect(440, 150, 115, 19));
        hmm = new QRadioButton(centralWidget);
        hmm->setObjectName(QStringLiteral("hmm"));
        hmm->setGeometry(QRect(440, 180, 115, 19));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(482, 210, 71, 21));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(440, 210, 72, 15));
        othello->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(othello);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 846, 26));
        othello->setMenuBar(menuBar);
        mainToolBar = new QToolBar(othello);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        othello->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(othello);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        othello->setStatusBar(statusBar);

        retranslateUi(othello);

        QMetaObject::connectSlotsByName(othello);
    } // setupUi

    void retranslateUi(QMainWindow *othello)
    {
        othello->setWindowTitle(QApplication::translate("othello", "othello", Q_NULLPTR));
        pushButton->setText(QApplication::translate("othello", "start", Q_NULLPTR));
        aim->setText(QApplication::translate("othello", "ai-mode", Q_NULLPTR));
        hmm->setText(QApplication::translate("othello", "human-mode", Q_NULLPTR));
        lineEdit->setText(QString());
        label->setText(QApplication::translate("othello", "dfct", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class othello: public Ui_othello {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OTHELLO_H
