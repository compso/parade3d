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
