
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

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;

Mandelbrot mandelbrot (WINDOW_WIDTH, WINDOW_HEIGHT);

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
	}
	glutPostRedisplay();
}
void specialFunction(int key, int x, int y){
	switch(key){
		case GLUT_KEY_LEFT:
			mandelbrot.goLeft();
			break;
		case GLUT_KEY_RIGHT:
			mandelbrot.goRight();
			break;
		case GLUT_KEY_UP:
			mandelbrot.goUp();
			break;
		case GLUT_KEY_DOWN:
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
	glutDisplayFunc( myDisplay );
	myInit();
	glutKeyboardFunc(myKeyInput);
	glutSpecialFunc(specialFunction);
	glutMainLoop( );
}



