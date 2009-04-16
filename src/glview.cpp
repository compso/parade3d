/****************************************************************************
Custom libQGLViewer declaration added primative commands

*****************************************************************************/

#include "glview.h"
#include "objects.h"
#include "formats/Mesh.h"
#include <math.h>
#include <qtimer.h>
#include <string.h>
#include <stdlib.h>
#include <qfiledialog.h>
#include <Cg/cg.h>		/* Cg Core API: Can't include this?  Is Cg Toolkit installed! */
#include <Cg/cgGL.h>	/* Cg OpenGL API (part of Cg Toolkit) */

#ifdef _WIN32
#include <sys/time.h>
#endif

std::vector<XMesh*> meshes;

using namespace std;
using namespace qglviewer;

GLfloat polyfactor = 1.0;
GLfloat polyunits = 1.0;

GLView::GLView(QWidget *parent)
    : QGLViewer(parent)
{
	Objects* s = new Objects();
	s->frame.setPosition(Vec(-0.5, -0.5, 0.0));
	scene_.append(s);
}

void GLView::loadFile(QString filename)
{
	QString name;
	if (filename.isEmpty()){ 
		QStringList filters;
		QStringList names;
		filters << "Mesh files (*.msh *.MSH)"
				<< "3DS (*.3ds)"
				<< "Candylab Mesh (*.ca *.cb)"
				<< "Any files (*)";
				QFileDialog dialog(this); 
				dialog.setFilters(filters); 
				dialog.setWindowTitle("Choose Model to load");
				if (dialog.exec()){
					names = dialog.selectedFiles();
					name = names[0];
				}
	} else {
		name = filename;
	}

// In case of Cancel
	if (name.isEmpty())
		return;

	clearScene();
	LoadMeshFile(name.toLatin1().constData(), meshes);
	camera()->setSceneBoundingBox(Vec (-5, -5, -5), Vec (5, 5, 5));
	camera()->showEntireScene();
	camera()->setZNearCoefficient(0.05f);
	updateGL();
	stopAnimation();
}

void GLView::init()
{
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	setKeyDescription(Qt::Key_L, "Loads a new mesh file");
	//restoreStateFromFile();
}

void GLView::homeView()
{
        // set orientation back
        camera()->setPosition(Vec(1.691655,0.858533,1.675499));
        camera()->setOrientation(Quaternion(-0.161387,0.387169,0.071684,0.904940));
        updateGL();
}

void GLView::clearScene()
{
	
	scene_.clear();
	spirals_.clear();
	cubes_.clear();
	meshes.clear();
        // set orientation back
        homeView();
}


void GLView::draw()
{
	//set bgcolor start
	qglClearColor(QColor(100,100,125,0));

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix ();

	//enable wireframe
	//glEnable(GL_LINE_SMOOTH);
	
	//enable flat
	glDisable(GL_LIGHTING);
	glShadeModel(GL_FLAT);
	
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(polyfactor, polyunits);

	//enable smooth polys
	//glEnable(GL_POLYGON_SMOOTH);
	//glShadeModel(GL_SMOOTH);
	
	//enable texture preview

	for (int i=0; i<int(scene_.size()); i++)
		scene_.at(i)->draw();
	
	DrawMeshes(meshes);
		
	if (int(spirals_.size()) >= 1){
		for (int i=0; i<int(spirals_.size()); i++)
			spirals_.at(i)->spiral(false, 0,0,0);
	}
	
	if (int(cubes_.size()) >= 1){
		for (int i=0; i<int(cubes_.size()); i++)
			cubes_.at(i)->cube(false,0,0,0);
	}
	
	glDisable(GL_POLYGON_OFFSET_FILL);

	//enable wire overlay
	glDisable(GL_LIGHTING);
	glColor3f (0,0,0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	for (int i=0; i<int(scene_.size()); i++)
		scene_.at(i)->draw();
	
	DrawMeshes(meshes);
		
	if (int(spirals_.size()) >= 1){
		for (int i=0; i<int(spirals_.size()); i++)
			spirals_.at(i)->spiral(true,0,0,0);
	}
	
	if (int(cubes_.size()) >= 1){
		for (int i=0; i<int(cubes_.size()); i++)
			cubes_.at(i)->cube(true,0,0,0);
	}
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glPopMatrix ();
	glFlush ();

	qglColor(foregroundColor());
	//grid
	if (parGridIsDrawn()) { glLineWidth(1.0); myDrawGrid(camera()->sceneRadius()); }
	
	//print the current camera position
	//Vec pos = camera()->position();
	//printf("current position %f,%f,%f\n", pos[0], pos[1], pos[2]);
	//Quaternion orr = camera()->orientation();
	//printf("current orientation %f,%f,%f,%f\n", orr[0], orr[1], orr[2], orr[3]);
}


void GLView::preDraw()
{
	QGLViewer::preDraw();
}

void GLView::drawCornerAxis()
{
	int viewport[4];
	int scissor[4];

	// The viewport and the scissor are changed to fit the lower left
	// corner. Original values are saved.
	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetIntegerv(GL_SCISSOR_BOX, scissor);

	// Axis viewport size, in pixels
	const int size = 50;
	glViewport(0,0,size,size);
	glScissor(0,0,size,size);

	// The Z-buffer is cleared to make the axis appear over the
	// original image.
	glClear(GL_DEPTH_BUFFER_BIT);

	// Tune for best line rendering
    glDisable(GL_LIGHTING);
	glLineWidth(2.0);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMultMatrixd(camera()->orientation().inverse().matrix());

	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 1.0);
	glEnd();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glEnable(GL_LIGHTING);

	// The viewport and the scissor are restored.
	glScissor(scissor[0],scissor[1],scissor[2],scissor[3]);
	glViewport(viewport[0],viewport[1],viewport[2],viewport[3]);
}

void GLView::drawSpiral()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//add spiral to object list
	Objects* o = new Objects();
	o->frame.setPosition(Vec(0.0, 0.0, 0.0));
	spirals_.append(o);
	updateGL();
}

void GLView::drawCube()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//add cube to object list
	Objects* o = new Objects();
	o->frame.setPosition(Vec(0.0, 0.0, 0.0));
	cubes_.append(o);
	updateGL();
}

/**
void GLView::gradent()
{	
	glDisable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
			glLoadIdentity();
			
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();
			
			glBegin(GL_QUADS);
			//bottom color
			glColor3f(0.1,0.1,0.2);
			glVertex2f(-1.0, -1.0);
			glVertex2f(1.0,-1.0);
			//top color
			glColor3f(0.5,0.5,0.8);
			glVertex2f(1.0, 1.0);
			glVertex2f(-1.0, 1.0);
			glEnd();
		
			glMatrixMode(GL_PROJECTION);
			glPopMatrix();
	
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	glEnable(GL_DEPTH_TEST);
}
**/

/*! Draws a grid in the XZ plane*/
void GLView::myDrawGrid(float size, int nbSubdivisions)
{
	GLboolean lighting;
	glGetBooleanv(GL_LIGHTING, &lighting);

	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	for (int i=0; i<=nbSubdivisions; ++i)
	{
		const float pos = size*(2.0*i/nbSubdivisions-1.0);
		glVertex3f(pos,0, -size);
		glVertex3f(pos,0, +size);
		glVertex3f(-size,0, pos);
		glVertex3f( size,0, pos);
	}
	glEnd();

	if (lighting)
		glEnable(GL_LIGHTING);
}

void GLView::postDraw()
{
	drawCornerAxis();
	QGLViewer::postDraw();
	
	//fps display
	if (parFPSIsDrawn()) { handleFPS();}
	
}


QString GLView::helpString() const
{
  QString text("<h2>Parade 3D</h2>");
  return text;
}


void GLView::drawFPS(double fpsRate)
{
	char buffer[200];
	
	glDisable(GL_DEPTH_TEST);
	glColor3f(1,1,1);
	sprintf(buffer, "fps %0.1f", fpsRate);
	//get buffer length
	int len = strlen( buffer ); 
	renderText(int(width()-(len*10)),int(height()-10), buffer);
	glEnable(GL_DEPTH_TEST);
}

static int myDrawFPS = 1;

#ifndef _WIN32
#include <sys/time.h> /* for gettimeofday and struct timeval */
#endif

void GLView::handleFPS(void)
{
  static int frameCount = 0;     /* Number of frames for timing */
  static double lastFpsRate = 0;
  /* Use BSD 4.2 gettimeofday system call for high-accuracy timing. */
  static struct timeval last_tp = { 0, 0 };
  struct timeval new_tp;
  double secs;
  
  gettimeofday(&new_tp, NULL);
  secs = (new_tp.tv_sec - last_tp.tv_sec) + (new_tp.tv_usec - last_tp.tv_usec)/1000000.0;
  if (secs >= 1.0) {
    lastFpsRate = frameCount / secs;
    last_tp = new_tp;
    frameCount = 0;
  }
  frameCount++;
  if (myDrawFPS) {
    drawFPS(lastFpsRate);
  }
}
