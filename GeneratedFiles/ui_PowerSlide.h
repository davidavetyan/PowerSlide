/********************************************************************************
** Form generated from reading UI file 'PowerSlide.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POWERSLIDE_H
#define UI_POWERSLIDE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PowerSlideClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *scrollAreaHorizontalLayout;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PowerSlideClass)
    {
        if (PowerSlideClass->objectName().isEmpty())
            PowerSlideClass->setObjectName(QString::fromUtf8("PowerSlideClass"));
        PowerSlideClass->resize(1200, 800);
        PowerSlideClass->setMinimumSize(QSize(1200, 800));
        PowerSlideClass->setAutoFillBackground(false);
        centralWidget = new QWidget(PowerSlideClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, -1, 6);
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1178, 720));
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        scrollAreaHorizontalLayout = new QHBoxLayout();
        scrollAreaHorizontalLayout->setSpacing(0);
        scrollAreaHorizontalLayout->setObjectName(QString::fromUtf8("scrollAreaHorizontalLayout"));
        scrollAreaHorizontalLayout->setContentsMargins(-1, -1, -1, 0);

        verticalLayout_3->addLayout(scrollAreaHorizontalLayout);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout->addWidget(scrollArea);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        PowerSlideClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PowerSlideClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1200, 21));
        PowerSlideClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PowerSlideClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setLayoutDirection(Qt::LeftToRight);
        mainToolBar->setAutoFillBackground(false);
        mainToolBar->setMovable(false);
        mainToolBar->setFloatable(true);
        PowerSlideClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PowerSlideClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        PowerSlideClass->setStatusBar(statusBar);

        retranslateUi(PowerSlideClass);

        QMetaObject::connectSlotsByName(PowerSlideClass);
    } // setupUi

    void retranslateUi(QMainWindow *PowerSlideClass)
    {
        PowerSlideClass->setWindowTitle(QCoreApplication::translate("PowerSlideClass", "PowerSlide", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PowerSlideClass: public Ui_PowerSlideClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POWERSLIDE_H
