/********************************************************************************
** Form generated from reading UI file 'CommandPane.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMANDPANE_H
#define UI_COMMANDPANE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CommandDockWidget
{
public:
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QLineEdit *lineEdit;

    void setupUi(QDockWidget *CommandDockWidget)
    {
        if (CommandDockWidget->objectName().isEmpty())
            CommandDockWidget->setObjectName(QString::fromUtf8("CommandDockWidget"));
        CommandDockWidget->resize(800, 160);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CommandDockWidget->sizePolicy().hasHeightForWidth());
        CommandDockWidget->setSizePolicy(sizePolicy);
        CommandDockWidget->setMaximumSize(QSize(524287, 160));
        CommandDockWidget->setFeatures(QDockWidget::DockWidgetClosable);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dockWidgetContents->sizePolicy().hasHeightForWidth());
        dockWidgetContents->setSizePolicy(sizePolicy1);
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        textEdit = new QTextEdit(dockWidgetContents);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy2);
        QFont font;
        font.setFamily(QString::fromUtf8("Courier New"));
        font.setPointSize(10);
        textEdit->setFont(font);

        verticalLayout->addWidget(textEdit);

        lineEdit = new QLineEdit(dockWidgetContents);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setFont(font);

        verticalLayout->addWidget(lineEdit);

        CommandDockWidget->setWidget(dockWidgetContents);

        retranslateUi(CommandDockWidget);

        QMetaObject::connectSlotsByName(CommandDockWidget);
    } // setupUi

    void retranslateUi(QDockWidget *CommandDockWidget)
    {
        CommandDockWidget->setWindowTitle(QCoreApplication::translate("CommandDockWidget", "Command Pane", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CommandDockWidget: public Ui_CommandDockWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMANDPANE_H
