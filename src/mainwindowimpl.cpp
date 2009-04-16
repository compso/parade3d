
#include "glview.h"
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
