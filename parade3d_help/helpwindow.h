#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QtGui/QMainWindow>

namespace Ui
{
    class helpWindowClass;
}

class helpWindow : public QMainWindow
{
    Q_OBJECT

public:
    helpWindow(QWidget *parent = 0);
    ~helpWindow();

private:
    Ui::helpWindowClass *ui;
};

#endif // HELPWINDOW_H
