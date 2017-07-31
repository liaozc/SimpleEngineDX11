/********************************************************************************
** Form generated from reading UI file 'simpleeditor.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMPLEEDITOR_H
#define UI_SIMPLEEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimpleEditorClass
{
public:
    QAction *actionOpenScene;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *NewScene;
    QMenu *OpenScene;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SimpleEditorClass)
    {
        if (SimpleEditorClass->objectName().isEmpty())
            SimpleEditorClass->setObjectName(QStringLiteral("SimpleEditorClass"));
        SimpleEditorClass->resize(600, 400);
        actionOpenScene = new QAction(SimpleEditorClass);
        actionOpenScene->setObjectName(QStringLiteral("actionOpenScene"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/SimpleEditor/Resources/FileOpen.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenScene->setIcon(icon);
        centralWidget = new QWidget(SimpleEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        SimpleEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SimpleEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        NewScene = new QMenu(menuBar);
        NewScene->setObjectName(QStringLiteral("NewScene"));
        OpenScene = new QMenu(menuBar);
        OpenScene->setObjectName(QStringLiteral("OpenScene"));
        SimpleEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SimpleEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        SimpleEditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        SimpleEditorClass->insertToolBarBreak(mainToolBar);
        statusBar = new QStatusBar(SimpleEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SimpleEditorClass->setStatusBar(statusBar);

        menuBar->addAction(NewScene->menuAction());
        menuBar->addAction(OpenScene->menuAction());
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionOpenScene);

        retranslateUi(SimpleEditorClass);

        QMetaObject::connectSlotsByName(SimpleEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *SimpleEditorClass)
    {
        SimpleEditorClass->setWindowTitle(QApplication::translate("SimpleEditorClass", "SimpleEditor", Q_NULLPTR));
        actionOpenScene->setText(QApplication::translate("SimpleEditorClass", "OpenScene", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionOpenScene->setToolTip(QApplication::translate("SimpleEditorClass", "\346\211\223\345\274\200\345\234\272\346\231\257", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        NewScene->setTitle(QApplication::translate("SimpleEditorClass", "\346\226\260\345\273\272", Q_NULLPTR));
        OpenScene->setTitle(QApplication::translate("SimpleEditorClass", "\346\211\223\345\274\200", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SimpleEditorClass: public Ui_SimpleEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMPLEEDITOR_H
