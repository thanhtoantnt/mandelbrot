/*
 * Mandelbulb.cpp
 *
 *  Created on: May 7, 2014
 *      Author: Leo
 */




#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <fstream>
#include <string>
#include <iostream>
#include <math.h>
#include "Mandelbulb.h"
using namespace std;

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;

int X_RANGE = 400;
int Y_RANGE = 400;
int Z_RANGE = 200;


Mandelbulb mandelbulb (X_RANGE, Y_RANGE, Z_RANGE, 20);

void setWindow(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}

void myInit( void ) {
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0 );
	glPointSize(1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void myDisplay( void )  {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0f,0.0f,0.0f);
	mandelbulb.draw();

	glColor3f(0.0f,1.0f,0.0f);
	glBegin(GL_LINES);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,1.0f);
	glEnd();

	glutSwapBuffers();
}

int main( int argc, char *argv[] )  {
  // Initialize GLUT.
  glutInit( &argc, argv );
  // Set the mode to draw in.
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
  // Set the window size in screen pixels.
  glutInitWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );
  // Set the window position in screen pixels.
  glutInitWindowPosition( 100, 150 );
  // Create the window.
  glutCreateWindow("Mandelbrot 3D");
  // Set the callback funcion to call when we need to draw something.
  glutDisplayFunc( myDisplay );
  //glutKeyboardFunc(myKeyInput);
  // Initialize some things.
  myInit( );
  // Now that we have set everything up, loop responding to events.
  glutMainLoop( );
}
