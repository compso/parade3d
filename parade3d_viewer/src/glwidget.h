/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the example classes of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

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

protected:
        virtual void postDraw();
        void initializeGL();
        void paintGL();
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
    int gear1Rot;
    
    QPoint lastPos;
};

#endif
