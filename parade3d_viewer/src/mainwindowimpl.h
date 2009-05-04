/************************************************

    Parade3d -- 3d model viewer
    Copyright (C) 2009 Ashley James Retallack

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

*************************************************/

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




