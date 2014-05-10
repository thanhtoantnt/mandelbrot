
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>

#include <fstream>
#include <string>
#include <iostream>
#include <math.h>

#include "Mandelbrot.h"

using namespace std;

/* -- GLOBAL VARIABLES -- */
int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;

Mandelbrot mandelbrot (WINDOW_WIDTH, WINDOW_HEIGHT);

void setWindow(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top)
{           glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D(left, right, bottom, top);
} 


void myInit( void ) {
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0 );
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D( 0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT );
}

void myDisplay( void )  {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0f,0.0f,0.0f);
	mandelbrot.draw();
	glutSwapBuffers();
}

void myKeyInput(unsigned char key, int x, int y){
	switch(key){
		case 'a':
			mandelbrot.zoomIn();
			break;
		case 'f':
			mandelbrot.zoomOut();
			break;
		case 's':
			mandelbrot.goLeft();
			break;
		case 'd':
			mandelbrot.goRight();
			break;
		case 'e':
			mandelbrot.goUp();
			break;
		case 'c':
			mandelbrot.goDown();
			break;
		
	}
	glutPostRedisplay();
}


int main( int argc, char *argv[] )  {
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );
	glutInitWindowPosition( 50, 50 );
	glutCreateWindow("Mandelbrot 2D");
	// Set the callback funcion to call when we need to draw something.
	glutDisplayFunc( myDisplay );
	// Initialize some things.
	myInit( );
	// Now that we have set everything up, loop responding to events.
	glutKeyboardFunc(myKeyInput);
	glutMainLoop( );
}



