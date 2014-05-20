
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

//global variables
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 640;
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
		case 'a':               // using key 'a' to zoom in
			mandelbrot.zoomIn();
			break;
		case 'f':
			mandelbrot.zoomOut();  // using key 'f' to zoom out
			break;
	}
	glutPostRedisplay();
}
void specialFunction(int key, int x, int y){
	switch(key){
		case GLUT_KEY_LEFT:   // using arrow key LEFT to go to the left
			mandelbrot.goLeft();
			break;
		case GLUT_KEY_RIGHT:   // using arrow key RIGHT to go to the right
			mandelbrot.goRight();
			break;
		case GLUT_KEY_UP:				// go up by UP arrow key
			mandelbrot.goUp();
			break;
		case GLUT_KEY_DOWN:			// go down by DOWN arrow key
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



