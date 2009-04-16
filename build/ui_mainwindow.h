/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
** Created: Thu Apr 16 09:55:31 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>
#include "../src/glview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionCube;
    QAction *actionGrid;
    QAction *actionAxis;
    QAction *actionOpen;
    QAction *actionSpiral;
    QAction *actionHelp;
    QAction *actionQuit;
    QAction *actionClear_Scene;
    QAction *actionSettings;
    QAction *actionShaded;
    QAction *actionWireframe;
    QAction *actionTextured;
    QAction *actionFps;
    QAction *actionFullscreen;
    QAction *actionDefault_Home;
    QAction *actionLighting;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    GLView *viewer;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuView;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::ApplicationModal);
        MainWindow->resize(598, 385);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(50, 50, 50);\n"
"selection-color: rgb(200, 200, 255);\n"
"alternate-background-color: rgb(80, 80, 80);\n"
"gridline-color: rgb(0, 0, 0);\n"
"border-color: rgb(60, 60, 60);\n"
"color: rgb(255, 255, 255);\n"
"selection-background-color: rgb(70, 70, 70);"));
        MainWindow->setUnifiedTitleAndToolBarOnMac(false);
        actionCube = new QAction(MainWindow);
        actionCube->setObjectName(QString::fromUtf8("actionCube"));
        actionGrid = new QAction(MainWindow);
        actionGrid->setObjectName(QString::fromUtf8("actionGrid"));
        actionGrid->setCheckable(true);
        actionGrid->setChecked(false);
        QIcon icon;
        icon.addPixmap(QPixmap(QString::fromUtf8(":/menu/cb/checkboxOff.png")), QIcon::Normal, QIcon::Off);
        icon.addPixmap(QPixmap(QString::fromUtf8(":/menu/cb/checkboxOn.png")), QIcon::Normal, QIcon::On);
        actionGrid->setIcon(icon);
        actionAxis = new QAction(MainWindow);
        actionAxis->setObjectName(QString::fromUtf8("actionAxis"));
        actionAxis->setCheckable(true);
        actionAxis->setChecked(true);
        actionAxis->setIcon(icon);
        actionAxis->setIconVisibleInMenu(false);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSpiral = new QAction(MainWindow);
        actionSpiral->setObjectName(QString::fromUtf8("actionSpiral"));
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionClear_Scene = new QAction(MainWindow);
        actionClear_Scene->setObjectName(QString::fromUtf8("actionClear_Scene"));
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QString::fromUtf8("actionSettings"));
        actionShaded = new QAction(MainWindow);
        actionShaded->setObjectName(QString::fromUtf8("actionShaded"));
        actionShaded->setCheckable(true);
        actionShaded->setIcon(icon);
        actionWireframe = new QAction(MainWindow);
        actionWireframe->setObjectName(QString::fromUtf8("actionWireframe"));
        actionWireframe->setCheckable(true);
        actionWireframe->setChecked(false);
        actionWireframe->setEnabled(true);
        actionWireframe->setIcon(icon);
        actionTextured = new QAction(MainWindow);
        actionTextured->setObjectName(QString::fromUtf8("actionTextured"));
        actionTextured->setCheckable(true);
        actionTextured->setIcon(icon);
        actionFps = new QAction(MainWindow);
        actionFps->setObjectName(QString::fromUtf8("actionFps"));
        actionFps->setCheckable(true);
        actionFps->setChecked(true);
        actionFps->setIcon(icon);
        actionFullscreen = new QAction(MainWindow);
        actionFullscreen->setObjectName(QString::fromUtf8("actionFullscreen"));
        actionFullscreen->setCheckable(true);
        actionFullscreen->setIcon(icon);
        actionDefault_Home = new QAction(MainWindow);
        actionDefault_Home->setObjectName(QString::fromUtf8("actionDefault_Home"));
        actionLighting = new QAction(MainWindow);
        actionLighting->setObjectName(QString::fromUtf8("actionLighting"));
        actionLighting->setCheckable(true);
        actionLighting->setIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setMargin(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        viewer = new GLView(centralwidget);
        viewer->setObjectName(QString::fromUtf8("viewer"));

        horizontalLayout->addWidget(viewer);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 598, 27));
        menubar->setAutoFillBackground(false);
        menubar->setStyleSheet(QString::fromUtf8("font: 8pt \"Sans Serif\";"));
        menubar->setDefaultUp(false);
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuFile->setStyleSheet(QString::fromUtf8(""));
        menuFile->setTearOffEnabled(false);
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuView->setStyleSheet(QString::fromUtf8(""));
        menuView->setSeparatorsCollapsible(false);
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuEdit->setStyleSheet(QString::fromUtf8(""));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuHelp->setStyleSheet(QString::fromUtf8(""));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionClear_Scene);
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuView->addSeparator();
        menuView->addAction(actionAxis);
        menuView->addAction(actionGrid);
        menuView->addAction(actionDefault_Home);
        menuView->addSeparator();
        menuView->addAction(actionFps);
        menuView->addAction(actionWireframe);
        menuView->addAction(actionTextured);
        menuView->addAction(actionShaded);
        menuView->addAction(actionLighting);
        menuView->addSeparator();
        menuView->addAction(actionFullscreen);
        menuEdit->addAction(actionCube);
        menuEdit->addAction(actionSpiral);
        menuEdit->addAction(actionSettings);
        menuHelp->addAction(actionHelp);

        retranslateUi(MainWindow);
        QObject::connect(actionGrid, SIGNAL(toggled(bool)), viewer, SLOT(parSetGridIsDrawn(bool)));
        QObject::connect(actionAxis, SIGNAL(toggled(bool)), viewer, SLOT(setAxisIsDrawn(bool)));
        QObject::connect(viewer, SIGNAL(parGridIsDrawnChanged(bool)), actionGrid, SLOT(setChecked(bool)));
        QObject::connect(viewer, SIGNAL(axisIsDrawnChanged(bool)), actionAxis, SLOT(setChecked(bool)));
        QObject::connect(actionOpen, SIGNAL(activated()), MainWindow, SLOT(OpenFile()));
        QObject::connect(actionHelp, SIGNAL(activated()), viewer, SLOT(help()));
        QObject::connect(actionQuit, SIGNAL(activated()), MainWindow, SLOT(close()));
        QObject::connect(actionSpiral, SIGNAL(activated()), viewer, SLOT(drawSpiral()));
        QObject::connect(actionCube, SIGNAL(activated()), viewer, SLOT(drawCube()));
        QObject::connect(actionClear_Scene, SIGNAL(activated()), viewer, SLOT(clearScene()));
        QObject::connect(actionFps, SIGNAL(toggled(bool)), viewer, SLOT(parSetFPSIsDrawn(bool)));
        QObject::connect(viewer, SIGNAL(parFPSIsDrawnChanged(bool)), actionFps, SLOT(setChecked(bool)));
        QObject::connect(actionFullscreen, SIGNAL(toggled(bool)), MainWindow, SLOT(parSetFullscreen(bool)));
        QObject::connect(MainWindow, SIGNAL(parFullscreenChanged(bool)), actionFullscreen, SLOT(setChecked(bool)));
        QObject::connect(actionDefault_Home, SIGNAL(activated()), viewer, SLOT(homeView()));
        QObject::connect(actionTextured, SIGNAL(activated()), actionWireframe, SLOT(toggle()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Parade 3D", 0, QApplication::UnicodeUTF8));
        actionCube->setText(QApplication::translate("MainWindow", "Cube", 0, QApplication::UnicodeUTF8));
        actionGrid->setText(QApplication::translate("MainWindow", "Grid", 0, QApplication::UnicodeUTF8));
        actionGrid->setShortcut(QApplication::translate("MainWindow", "G", 0, QApplication::UnicodeUTF8));
        actionAxis->setText(QApplication::translate("MainWindow", "Axis", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
        actionSpiral->setText(QApplication::translate("MainWindow", "Spiral", 0, QApplication::UnicodeUTF8));
        actionHelp->setText(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        actionClear_Scene->setText(QApplication::translate("MainWindow", "Clear Scene", 0, QApplication::UnicodeUTF8));
        actionSettings->setText(QApplication::translate("MainWindow", "Settings", 0, QApplication::UnicodeUTF8));
        actionShaded->setText(QApplication::translate("MainWindow", "Shaded", 0, QApplication::UnicodeUTF8));
        actionWireframe->setText(QApplication::translate("MainWindow", "Wireframe", 0, QApplication::UnicodeUTF8));
        actionTextured->setText(QApplication::translate("MainWindow", "Textured", 0, QApplication::UnicodeUTF8));
        actionFps->setText(QApplication::translate("MainWindow", "Fps", 0, QApplication::UnicodeUTF8));
        actionFps->setShortcut(QApplication::translate("MainWindow", "F", 0, QApplication::UnicodeUTF8));
        actionFullscreen->setText(QApplication::translate("MainWindow", "Fullscreen", 0, QApplication::UnicodeUTF8));
        actionFullscreen->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", 0, QApplication::UnicodeUTF8));
        actionDefault_Home->setText(QApplication::translate("MainWindow", "Default Home", 0, QApplication::UnicodeUTF8));
        actionLighting->setText(QApplication::translate("MainWindow", "Lighting", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("MainWindow", "View", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
