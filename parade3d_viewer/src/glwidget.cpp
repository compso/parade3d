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

#include <QtGui>
#include <QtOpenGL>

#include "objects.h"
#include "formats/Mesh.h"

#include <qtimer.h>
#include <qcursor.h>
#include <qmap.h>
#include <string.h>
#include <stdlib.h>
#include <qfiledialog.h>
#include <Cg/cg.h>		/* Cg Core API: Can't include this?  Is Cg Toolkit installed! */
#include <Cg/cgGL.h>	/* Cg OpenGL API (part of Cg Toolkit) */

# include <QKeyEvent>
# include <QMouseEvent>

#include <math.h>

#include "glwidget.h"

#ifdef _WIN32
#include <sys/time.h>
#endif

std::vector<XMesh*> meshes;

GLfloat polyfactor = 1.0;
GLfloat polyunits = 1.0;

using namespace std;


GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent)
{

        Objects* s = new Objects();
        s->frame.setPosition(-0.5, -0.5, 0.0);
        scene_.append(s);

    gear1 = 0;
    gear2 = 0;
    gear3 = 0;
    xRot = 0;
    yRot = 0;
    zRot = 0;
    zoom = -60.0f;
    gear1Rot = 0;

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(advanceGears()));
    timer->start(20);
}

GLWidget::~GLWidget()
{
    makeCurrent();
    glDeleteLists(gear1, 1);
    glDeleteLists(gear2, 1);
    glDeleteLists(gear3, 1);
}


void GLWidget::loadFile(QString filename)
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
        //camera()->setSceneBoundingBox(Vec (-5, -5, -5), Vec (5, 5, 5));
       // camera()->showEntireScene();
        //camera()->setZNearCoefficient(0.05f);
        updateGL();
}


void GLWidget::homeView()
{
        // set orientation back
        //camera()->setPosition(Vec(1.691655,0.858533,1.675499));
        //camera()->setOrientation(Quaternion(-0.161387,0.387169,0.071684,0.904940));
        updateGL();
}

void GLWidget::clearScene()
{

        scene_.clear();
        spirals_.clear();
        cubes_.clear();
        meshes.clear();
        // set orientation back
        homeView();
}


void GLWidget::drawCornerAxis()
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


void GLWidget::drawSpiral()
{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //add spiral to object list
        Objects* o = new Objects();
        o->frame.setPosition(0.0, 0.0, 0.0);
        spirals_.append(o);
        updateGL();
}

void GLWidget::drawCube()
{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //add cube to object list
        Objects* o = new Objects();
        o->frame.setPosition(0.0, 0.0, 0.0);
        cubes_.append(o);
        updateGL();
}


/*! Draws a grid in the XZ plane*/
void GLWidget::myDrawGrid(float size, int nbSubdivisions)
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


void GLWidget::postDraw()
{
        drawCornerAxis();

        //fps display
        if (parFPSIsDrawn()) { handleFPS();}

}



void GLWidget::drawFPS(double fpsRate)
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

void GLWidget::handleFPS(void)
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

void GLWidget::initializeGL()
{
    static const GLfloat lightPos[4] = { 5.0f, 5.0f, 10.0f, 1.0f };
    static const GLfloat reflectance1[4] = { 0.8f, 0.1f, 0.0f, 1.0f };
    static const GLfloat reflectance2[4] = { 0.0f, 0.8f, 0.2f, 1.0f };
    static const GLfloat reflectance3[4] = { 0.2f, 0.2f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

   // gear1 = makeGear(reflectance1, 1.0, 4.0, 1.0, 0.7, 20);
   // gear2 = makeGear(reflectance2, 0.5, 2.0, 2.0, 0.7, 10);
   // gear3 = makeGear(reflectance3, 1.3, 2.0, 0.5, 0.7, 10);

    glEnable(GL_NORMALIZE);
        //set bgcolor start
     //   qglClearColor(QColor(100,100,125,0));
    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}


void GLWidget::paintGL()
{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




        glPushMatrix();

        //get rotaion fom mouse movment

        glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
        glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
        glRotated(zRot / 16.0, 0.0, 0.0, 1.0);


        //set translation

        glTranslated(0.0, 0.0, zoom);

        // set too top view

        glRotated(+90.0, 1.0, 0.0, 0.0);

        qglClearColor(QColor(100,100,125,0));


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

        qglColor(QColor(255,255,255,255));

        //grid
        if (parGridIsDrawn()) { glLineWidth(1.0); myDrawGrid(10); }

        //print the current camera position
        //Vec pos = camera()->position();
        //printf("current position %f,%f,%f\n", pos[0], pos[1], pos[2]);
        //Quaternion orr = camera()->orientation();
        //printf("current orientation %f,%f,%f,%f\n", orr[0], orr[1], orr[2], orr[3]);



    glPopMatrix();


        drawCornerAxis();

        //fps display
        if (parFPSIsDrawn()) { handleFPS();}
}


void GLWidget::draw()
{

}

void GLWidget::resizeGL(int width, int height)
{
	
    int side = qMax(width, height);
    //glViewport( 0, 0, GLint(width), GLint(height) );
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, +1.0, -1.0, 1.0, 5.0, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0.0, 0.0, -60.0);

}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {

        setZoom(zoom+dy);
    }

    lastPos = event->pos();
}

void GLWidget::setZoom(float distance)
{
    if (distance != zoom) {
        zoom = distance;
        //emit zoomChanged(distance);
        updateGL();
    }
}

void GLWidget::setXRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::setYRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::setZRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::advanceGears()
{
    gear1Rot += 2 * 16;
    updateGL();
}

GLuint GLWidget::makeGear(const GLfloat *reflectance, GLdouble innerRadius,
                          GLdouble outerRadius, GLdouble thickness,
                          GLdouble toothSize, GLint toothCount)
{
    const double Pi = 3.14159265358979323846;

    GLuint list = glGenLists(1);
    glNewList(list, GL_COMPILE);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, reflectance);

    GLdouble r0 = innerRadius;
    GLdouble r1 = outerRadius - toothSize / 2.0;
    GLdouble r2 = outerRadius + toothSize / 2.0;
    GLdouble delta = (2.0 * Pi / toothCount) / 4.0;
    GLdouble z = thickness / 2.0;
    int i, j;

    glShadeModel(GL_FLAT);

    for (i = 0; i < 2; ++i) {
        GLdouble sign = (i == 0) ? +1.0 : -1.0;

        glNormal3d(0.0, 0.0, sign);

        glBegin(GL_QUAD_STRIP);
        for (j = 0; j <= toothCount; ++j) {
            GLdouble angle = 2.0 * Pi * j / toothCount;
	    glVertex3d(r0 * cos(angle), r0 * sin(angle), sign * z);
	    glVertex3d(r1 * cos(angle), r1 * sin(angle), sign * z);
	    glVertex3d(r0 * cos(angle), r0 * sin(angle), sign * z);
	    glVertex3d(r1 * cos(angle + 3 * delta), r1 * sin(angle + 3 * delta),
                       sign * z);
        }
        glEnd();

        glBegin(GL_QUADS);
        for (j = 0; j < toothCount; ++j) {
            GLdouble angle = 2.0 * Pi * j / toothCount;
	    glVertex3d(r1 * cos(angle), r1 * sin(angle), sign * z);
	    glVertex3d(r2 * cos(angle + delta), r2 * sin(angle + delta),
                       sign * z);
	    glVertex3d(r2 * cos(angle + 2 * delta), r2 * sin(angle + 2 * delta),
                       sign * z);
	    glVertex3d(r1 * cos(angle + 3 * delta), r1 * sin(angle + 3 * delta),
                       sign * z);
        }
        glEnd();
    }

    glBegin(GL_QUAD_STRIP);
    for (i = 0; i < toothCount; ++i) {
        for (j = 0; j < 2; ++j) {
            GLdouble angle = 2.0 * Pi * (i + (j / 2.0)) / toothCount;
            GLdouble s1 = r1;
            GLdouble s2 = r2;
            if (j == 1)
                qSwap(s1, s2);

	    glNormal3d(cos(angle), sin(angle), 0.0);
	    glVertex3d(s1 * cos(angle), s1 * sin(angle), +z);
	    glVertex3d(s1 * cos(angle), s1 * sin(angle), -z);

	    glNormal3d(s2 * sin(angle + delta) - s1 * sin(angle),
                       s1 * cos(angle) - s2 * cos(angle + delta), 0.0);
	    glVertex3d(s2 * cos(angle + delta), s2 * sin(angle + delta), +z);
	    glVertex3d(s2 * cos(angle + delta), s2 * sin(angle + delta), -z);
        }
    }
    glVertex3d(r1, 0.0, +z);
    glVertex3d(r1, 0.0, -z);
    glEnd();

    glShadeModel(GL_SMOOTH);

    glBegin(GL_QUAD_STRIP);
    for (i = 0; i <= toothCount; ++i) {
	GLdouble angle = i * 2.0 * Pi / toothCount;
	glNormal3d(-cos(angle), -sin(angle), 0.0);
	glVertex3d(r0 * cos(angle), r0 * sin(angle), +z);
	glVertex3d(r0 * cos(angle), r0 * sin(angle), -z);
    }
    glEnd();

    glEndList();

    return list;
}

void GLWidget::drawGear(GLuint gear, GLdouble dx, GLdouble dy, GLdouble dz,
                        GLdouble angle)
{
    glPushMatrix();
    glTranslated(dx, dy, dz);
    glRotated(angle, 0.0, 0.0, 1.0);
    glCallList(gear);
    glPopMatrix();
}

void GLWidget::normalizeAngle(int *angle)
{
    while (*angle < 0)
        *angle += 360 * 16;
    while (*angle > 360 * 16)
        *angle -= 360 * 16;
}
