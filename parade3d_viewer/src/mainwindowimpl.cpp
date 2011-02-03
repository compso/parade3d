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

#include "glwidget.h"
#include "mainwindowimpl.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "objects.h"
#include "formats/Mesh.h"

using namespace std;

//
MainWindowImpl::MainWindowImpl( QWidget * parent, Qt::WFlags f) 
	: QMainWindow(parent, f)
{
	setupUi(this);
	// Restore the previous viewer state.
	//setup viewer scene
        viewer->clearScene();
	viewer->updateGL();
        viewer->parSetGridIsDrawn(true);
        viewer->parSetFPSIsDrawn(true);
	
	//connect(actionFullscreen, SIGNAL(toggled(bool)), MainWindow, SLOT(fullscreen(bool)));
	
}

void MainWindowImpl::OpenFile()
{
        viewer->loadFile("");
}

void MainWindowImpl::cube()
{
	printf("// Cube Drawn \n");
        viewer->drawCube();
}

void MainWindowImpl::spiral()
{
	printf("// Spiral Drawn \n");
        viewer->drawSpiral();
}

//
