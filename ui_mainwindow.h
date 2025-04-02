/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *portSpinBox;
    QPushButton *startButton;
    QPushButton *stopButton;
    QSpacerItem *horizontalSpacer;
    QLabel *statusLabel;
    QTextEdit *chatDisplay;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *messageInput;
    QPushButton *sendButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(500, 500);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        portSpinBox = new QSpinBox(centralwidget);
        portSpinBox->setObjectName("portSpinBox");
        portSpinBox->setMinimum(1024);
        portSpinBox->setMaximum(65535);
        portSpinBox->setValue(8080);

        horizontalLayout->addWidget(portSpinBox);

        startButton = new QPushButton(centralwidget);
        startButton->setObjectName("startButton");

        horizontalLayout->addWidget(startButton);

        stopButton = new QPushButton(centralwidget);
        stopButton->setObjectName("stopButton");

        horizontalLayout->addWidget(stopButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        statusLabel = new QLabel(centralwidget);
        statusLabel->setObjectName("statusLabel");

        verticalLayout->addWidget(statusLabel);

        chatDisplay = new QTextEdit(centralwidget);
        chatDisplay->setObjectName("chatDisplay");
        chatDisplay->setReadOnly(true);

        verticalLayout->addWidget(chatDisplay);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        messageInput = new QLineEdit(centralwidget);
        messageInput->setObjectName("messageInput");

        horizontalLayout_2->addWidget(messageInput);

        sendButton = new QPushButton(centralwidget);
        sendButton->setObjectName("sendButton");

        horizontalLayout_2->addWidget(sendButton);


        verticalLayout->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 500, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Qt Messaging Server", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Port:", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "Start Server", nullptr));
        stopButton->setText(QCoreApplication::translate("MainWindow", "Stop Server", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "Server is stopped", nullptr));
        messageInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "Type a message to broadcast...", nullptr));
        sendButton->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
