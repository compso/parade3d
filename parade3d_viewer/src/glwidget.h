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

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QAction>

#include "objects.h"

/** File formats **/
#include "formats/Mesh.h"
/** **/

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    static void myDrawGrid(float size=1.0f, int nbSubdivisions=10);
    bool parGridIsDrawn() const { return parGridIsDrawn_; }
    bool parFPSIsDrawn() const { return parFPSIsDrawn_; }

    int xRotation() const { return xRot; }
    int yRotation() const { return yRot; }
    int zRotation() const { return zRot; }


public slots :
        void homeView();
        void clearScene();
        void drawSpiral();
        void drawCube();
        void loadFile(QString filename);
        //Grid
        void parSetGridIsDrawn(bool draw=true) { parGridIsDrawn_ = draw; emit parGridIsDrawnChanged(draw); updateGL(); }
        void parToggleGridIsDrawn() { parSetGridIsDrawn(!parGridIsDrawn()); }
        //FPS
        void parSetFPSIsDrawn(bool draw=true) { parFPSIsDrawn_ = draw; emit parFPSIsDrawnChanged(draw); updateGL(); }
        void parToggleFPSIsDrawn() { parSetFPSIsDrawn(!parFPSIsDrawn()); }
        //Axis
        void parSetAxisIsDrawn(bool draw=true) { parFPSIsDrawn_ = draw; emit parFPSIsDrawnChanged(draw); updateGL(); }
        void parToggleAxisIsDrawn() { parSetFPSIsDrawn(!parFPSIsDrawn()); }
        //Draw Mode default 9=poly display, 3=wireframe
        void setMode(int mode=9) { drawMode_ = mode; emit modeChanged(mode); updateGL(); }
        void setXRotation(int angle);
        void setYRotation(int angle);
        void setZRotation(int angle);
        void setZoom(float distance);

signals:
        void parGridIsDrawnChanged(bool drawn);
        void parFPSIsDrawnChanged(bool drawn);
        void parAxisIsDrawnChanged(bool drawn);
        void parWireView(bool wire);
        void parShadeView(bool shade);
        void parTexView(bool tex);
        void parFlatView(bool tex);
        void modeChanged(int mode);
        void xRotationChanged(int angle);
        void yRotationChanged(int angle);
        void zRotationChanged(int angle);
        void zoomChanged(float zoom);

protected:
        virtual void postDraw();
        void initializeGL();
        void paintGL();
        void draw();
        void resizeGL(int width, int height);
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);

private slots:
    void advanceGears();

private:
        void drawCornerAxis();
        QList<Objects*> scene_;
        QList<Objects*> spirals_;
        QList<Objects*> cubes_;
        void drawFPS(double fpsRate);
        void handleFPS(void);
        void gradent();
        //HUD Element detection
        bool parGridIsDrawn_;
        bool parFPSIsDrawn_;
        int drawMode_;
        bool wireframe_, flatShading_;

    GLuint makeGear(const GLfloat *reflectance, GLdouble innerRadius,
                    GLdouble outerRadius, GLdouble thickness,
                    GLdouble toothSize, GLint toothCount);
    void drawGear(GLuint gear, GLdouble dx, GLdouble dy, GLdouble dz,
                  GLdouble angle);
    void normalizeAngle(int *angle);

    GLuint gear1;
    GLuint gear2;
    GLuint gear3;
    int xRot;
    int yRot;
    int zRot;
    float zoom;
    int gear1Rot;
    
    QPoint lastPos;
};

#endif
