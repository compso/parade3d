#ifndef OBJECTS_H_
#define OBJECTS_H_

#include <qobject.h>
#include "QGLViewer/frame.h"

class QGLViewer;

class Objects : public QObject
{
  Q_OBJECT
public :
	void draw() const;
	qglviewer::Frame frame;
public slots:
	void spiral(bool wire, float r, float g, float b);
	void cube(bool wire, float r, float g, float b);

};

#endif // OBJECT_H_
