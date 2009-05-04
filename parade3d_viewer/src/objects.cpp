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

#include <qgl.h>
#include "objects.h"
#include <math.h>

using namespace qglviewer;

void Objects::draw() const
{
}

// Draws a spiral
void Objects::spiral(bool wire, float r, float g, float b)
{
	const float nbSteps = 200.0;
	glBegin(GL_QUAD_STRIP);
	for (float i=0; i<nbSteps; ++i)
		{
			float ratio = i/nbSteps;
			float angle = 21.0*ratio;
			float c = cos(angle);
			float s = sin(angle);
			float r1 = 1.0 - 0.8*ratio;
			float r2 = 0.8 - 0.8*ratio;
			float alt = ratio - 0.5;
			const float nor = .5;
			const float up = sqrt(1.0-nor*nor);
			if (!wire){
				glColor3f(1.0-ratio, 0.2f , ratio);
			} else {
				glColor3f(r,g,b);
			}
			glNormal3f(nor*c, up, nor*s);
			glVertex3f(r1*c, alt, r1*s);
			glVertex3f(r2*c, alt+0.05, r2*s);
		}
	glEnd();
}

// Draws a cube
void Objects::cube(bool wire, float r, float g, float b)
{
	glPushMatrix();
	glBegin(GL_QUADS);
			if (!wire){
				glColor3f(1.0, 0.0 , 0.0);
			} else {
				glColor3f(r,g,b);
			}
	
			/*      This is the front face*/
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
			
			/*      This is the back face*/
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, -0.5f, -0.5f);
	
			/*      This is the top face*/
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(0.5f, 0.5f, -0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
			
			/*      This is the bottom face*/
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
			
			/*      This is the right face*/
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, 0.5f, -0.5f);
			
			/*      This is the left face*/
			glVertex3f(-0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();
	glPopMatrix();
}
