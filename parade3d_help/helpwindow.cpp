#include "helpwindow.h"
#include "ui_helpwindow.h"

helpWindow::helpWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::helpWindowClass)
{
    ui->setupUi(this);
}

helpWindow::~helpWindow()
{
    delete ui;
}
