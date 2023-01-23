/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEdit;
    QPushButton *dolaczButton;
    QTextBrowser *textBrowser;
    QGroupBox *groupBox;
    QTextBrowser *textBrowser_2;
    QPushButton *pushButton_2;
    QFrame *z1;
    QFrame *z2;
    QFrame *z3;
    QFrame *z4;
    QFrame *z5;
    QLabel *z6;
    QLabel *z7;
    QLabel *z8;
    QTextBrowser *textBrowser_3;
    QLineEdit *lineEdit_2;
    QTextBrowser *textBrowser_4;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEdit_3;
    QLabel *label_5;
    QLabel *label_6;
    QSpinBox *spinBox;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(398, 431);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(255, 170, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        MainWindow->setPalette(palette);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush2(QColor(170, 255, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush2);
        centralWidget->setPalette(palette1);
        gridLayoutWidget_2 = new QWidget(centralWidget);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(10, -1, 381, 131));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(gridLayoutWidget_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        QPalette palette2;
        QBrush brush3(QColor(0, 0, 255, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        QBrush brush4(QColor(170, 255, 255, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush4);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush4);
        QBrush brush5(QColor(190, 190, 190, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush5);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        lineEdit->setPalette(palette2);

        gridLayout_2->addWidget(lineEdit, 1, 0, 1, 1);

        dolaczButton = new QPushButton(gridLayoutWidget_2);
        dolaczButton->setObjectName(QStringLiteral("dolaczButton"));
        QPalette palette3;
        QBrush brush6(QColor(85, 255, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush6);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush6);
        dolaczButton->setPalette(palette3);

        gridLayout_2->addWidget(dolaczButton, 2, 0, 1, 1);

        textBrowser = new QTextBrowser(gridLayoutWidget_2);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        QPalette palette4;
        QBrush brush7(QColor(255, 255, 127, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette4.setBrush(QPalette::Active, QPalette::Base, brush7);
        palette4.setBrush(QPalette::Active, QPalette::Window, brush7);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush7);
        palette4.setBrush(QPalette::Inactive, QPalette::Window, brush7);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush7);
        palette4.setBrush(QPalette::Disabled, QPalette::Window, brush7);
        textBrowser->setPalette(palette4);

        gridLayout_2->addWidget(textBrowser, 0, 0, 1, 1);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setEnabled(false);
        groupBox->setGeometry(QRect(9, 139, 381, 211));
        textBrowser_2 = new QTextBrowser(groupBox);
        textBrowser_2->setObjectName(QStringLiteral("textBrowser_2"));
        textBrowser_2->setGeometry(QRect(0, 0, 381, 51));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::Base, brush);
        palette5.setBrush(QPalette::Active, QPalette::Window, brush7);
        palette5.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Window, brush7);
        palette5.setBrush(QPalette::Disabled, QPalette::Base, brush7);
        palette5.setBrush(QPalette::Disabled, QPalette::Window, brush7);
        textBrowser_2->setPalette(palette5);
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(300, 180, 80, 31));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::Button, brush6);
        palette6.setBrush(QPalette::Inactive, QPalette::Button, brush6);
        palette6.setBrush(QPalette::Disabled, QPalette::Button, brush6);
        pushButton_2->setPalette(palette6);
        z1 = new QFrame(groupBox);
        z1->setObjectName(QStringLiteral("z1"));
        z1->setGeometry(QRect(40, 170, 20, 31));
        z1->setFrameShape(QFrame::VLine);
        z1->setFrameShadow(QFrame::Sunken);
        z2 = new QFrame(groupBox);
        z2->setObjectName(QStringLiteral("z2"));
        z2->setGeometry(QRect(40, 130, 20, 31));
        z2->setFrameShape(QFrame::VLine);
        z2->setFrameShadow(QFrame::Sunken);
        z3 = new QFrame(groupBox);
        z3->setObjectName(QStringLiteral("z3"));
        z3->setGeometry(QRect(40, 90, 20, 31));
        z3->setFrameShape(QFrame::VLine);
        z3->setFrameShadow(QFrame::Sunken);
        z4 = new QFrame(groupBox);
        z4->setObjectName(QStringLiteral("z4"));
        z4->setGeometry(QRect(60, 80, 31, 16));
        z4->setFrameShape(QFrame::HLine);
        z4->setFrameShadow(QFrame::Sunken);
        z5 = new QFrame(groupBox);
        z5->setObjectName(QStringLiteral("z5"));
        z5->setGeometry(QRect(80, 90, 20, 31));
        z5->setFrameShape(QFrame::VLine);
        z5->setFrameShadow(QFrame::Sunken);
        z6 = new QLabel(groupBox);
        z6->setObjectName(QStringLiteral("z6"));
        z6->setGeometry(QRect(80, 120, 20, 16));
        z7 = new QLabel(groupBox);
        z7->setObjectName(QStringLiteral("z7"));
        z7->setGeometry(QRect(80, 130, 59, 16));
        z8 = new QLabel(groupBox);
        z8->setObjectName(QStringLiteral("z8"));
        z8->setGeometry(QRect(80, 140, 16, 20));
        textBrowser_3 = new QTextBrowser(groupBox);
        textBrowser_3->setObjectName(QStringLiteral("textBrowser_3"));
        textBrowser_3->setGeometry(QRect(190, 140, 171, 31));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::Base, brush7);
        palette7.setBrush(QPalette::Active, QPalette::Window, brush7);
        palette7.setBrush(QPalette::Inactive, QPalette::Base, brush7);
        palette7.setBrush(QPalette::Inactive, QPalette::Window, brush7);
        palette7.setBrush(QPalette::Disabled, QPalette::Base, brush7);
        palette7.setBrush(QPalette::Disabled, QPalette::Window, brush7);
        textBrowser_3->setPalette(palette7);
        lineEdit_2 = new QLineEdit(groupBox);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(232, 180, 61, 23));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::Base, brush);
        palette8.setBrush(QPalette::Active, QPalette::Window, brush4);
        palette8.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::Window, brush4);
        palette8.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        palette8.setBrush(QPalette::Disabled, QPalette::Window, brush4);
        lineEdit_2->setPalette(palette8);
        textBrowser_4 = new QTextBrowser(groupBox);
        textBrowser_4->setObjectName(QStringLiteral("textBrowser_4"));
        textBrowser_4->setGeometry(QRect(190, 80, 171, 31));
        QPalette palette9;
        palette9.setBrush(QPalette::Active, QPalette::Base, brush7);
        palette9.setBrush(QPalette::Active, QPalette::Window, brush7);
        palette9.setBrush(QPalette::Inactive, QPalette::Base, brush7);
        palette9.setBrush(QPalette::Inactive, QPalette::Window, brush7);
        palette9.setBrush(QPalette::Disabled, QPalette::Base, brush7);
        palette9.setBrush(QPalette::Disabled, QPalette::Window, brush7);
        textBrowser_4->setPalette(palette9);
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(230, 120, 91, 21));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(220, 60, 131, 20));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(130, 180, 101, 20));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 350, 141, 16));
        lineEdit_3 = new QLineEdit(centralWidget);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(80, 370, 113, 23));
        QPalette palette10;
        palette10.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette10.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette10.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        lineEdit_3->setPalette(palette10);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 370, 51, 16));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(240, 370, 31, 16));
        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(280, 370, 81, 24));
        QPalette palette11;
        palette11.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette11.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette11.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        spinBox->setPalette(palette11);
        spinBox->setMaximum(100000);
        spinBox->setValue(8090);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 398, 20));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        lineEdit->setText(QApplication::translate("MainWindow", "Podaj swoja nazwe uzytykownika", 0));
        dolaczButton->setText(QApplication::translate("MainWindow", "Dolacz do gry", 0));
        textBrowser->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; font-weight:600; color:#000000;\">GRA W WISIELCA!</span></p></body></html>", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "GroupBox", 0));
        textBrowser_2->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">&lt;komunikaty z gry&gt;</p></body></html>", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Wyslij", 0));
        z6->setText(QApplication::translate("MainWindow", "O", 0));
        z7->setText(QApplication::translate("MainWindow", "/I\\", 0));
        z8->setText(QApplication::translate("MainWindow", "/\\", 0));
        label->setText(QApplication::translate("MainWindow", "Aktualne haslo", 0));
        label_2->setText(QApplication::translate("MainWindow", "Wykorzystane literki", 0));
        label_3->setText(QApplication::translate("MainWindow", "Wybierz literke", 0));
        label_4->setText(QApplication::translate("MainWindow", "Ustawienia polaczenia;", 0));
        lineEdit_3->setText(QApplication::translate("MainWindow", "127.0.0.1", 0));
        label_5->setText(QApplication::translate("MainWindow", "Adres:", 0));
        label_6->setText(QApplication::translate("MainWindow", "Port:", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
