#ifndef MAINWINDOWIMPL_H
#define MAINWINDOWIMPL_H
//

#include <QMainWindow>
#include "ui_mainwindow.h"
//
class MainWindowImpl : public QMainWindow, public Ui::MainWindow
{
Q_OBJECT
public:
	MainWindowImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
private slots:
	void OpenFile();
	void cube();
	void spiral();
	void parSetFullscreen(bool set=true) {emit parFullscreenChanged(set);if (set){
			this->showFullScreen();
		} else {
			this->showNormal();
		}
	};
signals:
	void parFullscreenChanged(bool set);
protected :	
};
#endif




