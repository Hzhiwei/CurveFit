/********************************************************************************
** Form generated from reading UI file 'mainwindows.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOWS_H
#define UI_MAINWINDOWS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainWindowsClass
{
public:
    QWidget *centralWidget;
    QLabel *L_srcImage;
    QLabel *L_fitImage;
    QLabel *L_adjImage;
    QPushButton *PB_open;
    QScrollBar *SB_thresh;
    QLabel *L_conImage;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *L_thresh;
    QLabel *label_5;
    QScrollBar *SB_maxAllowSqError1;
    QLabel *L_maxAllowSqError1;
    QScrollBar *SB_maxAllowSqError2;
    QLabel *L_maxAllowSqError2;
    QLabel *L_bezierNum;
    QLabel *L_conNum;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *mainWindowsClass)
    {
        if (mainWindowsClass->objectName().isEmpty())
            mainWindowsClass->setObjectName(QStringLiteral("mainWindowsClass"));
        mainWindowsClass->resize(677, 659);
        centralWidget = new QWidget(mainWindowsClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        L_srcImage = new QLabel(centralWidget);
        L_srcImage->setObjectName(QStringLiteral("L_srcImage"));
        L_srcImage->setGeometry(QRect(10, 100, 320, 240));
        L_srcImage->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"	border:1px solid rgb(0,0,0);\n"
"}"));
        L_fitImage = new QLabel(centralWidget);
        L_fitImage->setObjectName(QStringLiteral("L_fitImage"));
        L_fitImage->setGeometry(QRect(340, 350, 320, 240));
        L_fitImage->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"	border:1px solid rgb(0,0,0);\n"
"}"));
        L_adjImage = new QLabel(centralWidget);
        L_adjImage->setObjectName(QStringLiteral("L_adjImage"));
        L_adjImage->setGeometry(QRect(340, 100, 320, 240));
        L_adjImage->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"	border:1px solid rgb(0,0,0);\n"
"}"));
        PB_open = new QPushButton(centralWidget);
        PB_open->setObjectName(QStringLiteral("PB_open"));
        PB_open->setGeometry(QRect(10, 10, 101, 23));
        SB_thresh = new QScrollBar(centralWidget);
        SB_thresh->setObjectName(QStringLiteral("SB_thresh"));
        SB_thresh->setGeometry(QRect(250, 10, 361, 20));
        SB_thresh->setStyleSheet(QStringLiteral(""));
        SB_thresh->setMaximum(255);
        SB_thresh->setValue(128);
        SB_thresh->setOrientation(Qt::Horizontal);
        L_conImage = new QLabel(centralWidget);
        L_conImage->setObjectName(QStringLiteral("L_conImage"));
        L_conImage->setGeometry(QRect(10, 350, 321, 241));
        L_conImage->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"	border:1px solid rgb(0,0,0);\n"
"}"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(190, 10, 31, 20));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 50, 54, 16));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 70, 91, 16));
        L_thresh = new QLabel(centralWidget);
        L_thresh->setObjectName(QStringLiteral("L_thresh"));
        L_thresh->setGeometry(QRect(630, 10, 31, 16));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(130, 40, 111, 16));
        SB_maxAllowSqError1 = new QScrollBar(centralWidget);
        SB_maxAllowSqError1->setObjectName(QStringLiteral("SB_maxAllowSqError1"));
        SB_maxAllowSqError1->setGeometry(QRect(250, 40, 361, 20));
        SB_maxAllowSqError1->setStyleSheet(QStringLiteral(""));
        SB_maxAllowSqError1->setMaximum(200);
        SB_maxAllowSqError1->setValue(10);
        SB_maxAllowSqError1->setOrientation(Qt::Horizontal);
        L_maxAllowSqError1 = new QLabel(centralWidget);
        L_maxAllowSqError1->setObjectName(QStringLiteral("L_maxAllowSqError1"));
        L_maxAllowSqError1->setGeometry(QRect(630, 40, 31, 16));
        SB_maxAllowSqError2 = new QScrollBar(centralWidget);
        SB_maxAllowSqError2->setObjectName(QStringLiteral("SB_maxAllowSqError2"));
        SB_maxAllowSqError2->setGeometry(QRect(250, 70, 361, 20));
        SB_maxAllowSqError2->setStyleSheet(QStringLiteral(""));
        SB_maxAllowSqError2->setMinimum(1);
        SB_maxAllowSqError2->setMaximum(100);
        SB_maxAllowSqError2->setValue(1);
        SB_maxAllowSqError2->setOrientation(Qt::Horizontal);
        L_maxAllowSqError2 = new QLabel(centralWidget);
        L_maxAllowSqError2->setObjectName(QStringLiteral("L_maxAllowSqError2"));
        L_maxAllowSqError2->setGeometry(QRect(630, 70, 31, 16));
        L_bezierNum = new QLabel(centralWidget);
        L_bezierNum->setObjectName(QStringLiteral("L_bezierNum"));
        L_bezierNum->setGeometry(QRect(110, 70, 71, 16));
        L_conNum = new QLabel(centralWidget);
        L_conNum->setObjectName(QStringLiteral("L_conNum"));
        L_conNum->setGeometry(QRect(70, 50, 71, 16));
        mainWindowsClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(mainWindowsClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 677, 23));
        mainWindowsClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(mainWindowsClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainWindowsClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(mainWindowsClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        mainWindowsClass->setStatusBar(statusBar);

        retranslateUi(mainWindowsClass);

        QMetaObject::connectSlotsByName(mainWindowsClass);
    } // setupUi

    void retranslateUi(QMainWindow *mainWindowsClass)
    {
        mainWindowsClass->setWindowTitle(QApplication::translate("mainWindowsClass", "mainWindows", Q_NULLPTR));
        L_srcImage->setText(QString());
        L_fitImage->setText(QString());
        L_adjImage->setText(QString());
        PB_open->setText(QApplication::translate("mainWindowsClass", "open", Q_NULLPTR));
        L_conImage->setText(QString());
        label->setText(QApplication::translate("mainWindowsClass", "\351\230\210\345\200\274\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("mainWindowsClass", "\350\275\256\345\273\223\346\225\260\351\207\217\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("mainWindowsClass", "\350\264\235\345\241\236\345\260\224\347\211\207\346\256\265\346\225\260\351\207\217\357\274\232", Q_NULLPTR));
        L_thresh->setText(QApplication::translate("mainWindowsClass", "128", Q_NULLPTR));
        label_5->setText(QApplication::translate("mainWindowsClass", "\346\234\200\345\244\247\345\205\201\350\256\270\345\271\263\346\226\271\350\257\257\345\267\256\357\274\232", Q_NULLPTR));
        L_maxAllowSqError1->setText(QApplication::translate("mainWindowsClass", "10", Q_NULLPTR));
        L_maxAllowSqError2->setText(QApplication::translate("mainWindowsClass", "0.01", Q_NULLPTR));
        L_bezierNum->setText(QApplication::translate("mainWindowsClass", "-", Q_NULLPTR));
        L_conNum->setText(QApplication::translate("mainWindowsClass", "-", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class mainWindowsClass: public Ui_mainWindowsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWS_H
