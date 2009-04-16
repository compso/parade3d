/****************************************************************************


*****************************************************************************/

#ifndef GLVIEW_H
#define GLVIEW_H

#include <QGLViewer/qglviewer.h>
#include <QAction>
#include "objects.h"

/** File formats **/
#include "formats/Mesh.h"
/** **/

class GLView : public QGLViewer
{
	Q_OBJECT // object declaration required to add slots etc to QGLViewer Class
	
public :
	GLView(QWidget *parent);
	static void myDrawGrid(float size=1.0f, int nbSubdivisions=10);
	bool parGridIsDrawn() const { return parGridIsDrawn_; };
	bool parFPSIsDrawn() const { return parFPSIsDrawn_; };
	
public slots :
        void homeView();
        void clearScene();
	void drawSpiral();
	void drawCube();
	void loadFile(QString filename);
	//Grid
	void parSetGridIsDrawn(bool draw=true) { parGridIsDrawn_ = draw; emit parGridIsDrawnChanged(draw); updateGL(); };
	void parToggleGridIsDrawn() { parSetGridIsDrawn(!parGridIsDrawn()); };
	//FPS
	void parSetFPSIsDrawn(bool draw=true) { parFPSIsDrawn_ = draw; emit parFPSIsDrawnChanged(draw); updateGL(); };
	void parToggleFPSIsDrawn() { parSetFPSIsDrawn(!parFPSIsDrawn()); };
	//Draw Mode default 9=poly display, 3=wireframe
	void setMode(int mode=9) { drawMode_ = mode; emit modeChanged(mode); updateGL(); };

signals :
	void parGridIsDrawnChanged(bool drawn);
	void parFPSIsDrawnChanged(bool drawn);
	void parWireView(bool wire);
	void parShadeView(bool shade);
	void parTexView(bool tex);
	void parFlatView(bool tex);
	void modeChanged(int mode);

protected :
	 virtual void preDraw();
	 virtual void postDraw();
	 virtual void draw();
	 virtual void init();
	 virtual QString helpString() const;
  
private :
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

};

#endif // GLVIEW_H
