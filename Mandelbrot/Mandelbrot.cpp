#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>

#include "Mandelbrot.h"

// default construction
Mandelbrot::Mandelbrot(void){
}

// construction width creen width and height
// calculating initial values
Mandelbrot::Mandelbrot(int the_screenWidth, int the_screenHeight){
	minReal = -2.0; maxReal = 1.0;
	
	screenWidth = the_screenWidth; screenHeight = the_screenHeight;
	scaleReal = (maxReal - minReal)/screenWidth;

	minImg = -1.0; maxImg = 1.0;
	scaleImg = (maxImg - minImg)/ screenHeight;
	
	imgFactor = (maxReal - minReal)/40;
	realFactor = imgFactor*1.5;
 
	max_iteration = 35;
	
	cout << max_iteration << endl;
	createPointSet();	
}

//destruction
Mandelbrot::~Mandelbrot(void){
}

//create set of color of poins
void Mandelbrot::createPointSet(){
	int row, col, iteration;
	Complex c;
	Color color;
	
	c.img = minImg;
	for(row = 0; row < screenHeight; row++){
		c.real = minReal;
		for(col = 0; col < screenWidth; col++){
			Complex z(0,0);
			for(iteration = 0; iteration < max_iteration; iteration++){
				if(z.modulus() > 4){  // if absolute value of  complex number z is over 4, then it is not in Mandelbrot set
					break;
				}
				z = z * z + c;
			}
			
			// if the pixel is not in the Mandelbrot set, the coloring it
			if(iteration < max_iteration) { 
				color =  Color::coloring(iteration, max_iteration);
			}
			
			// if not, it is in the set, the its color is black
			else { color.red = color.green = color.blue = 0.0f; }
			point_set.push_back(color);  // push into the vector
			
			c.real += scaleReal;
		}
		c.img += scaleImg;
	}
}

// drawing depens on the point set, the set of colors of points
void Mandelbrot::draw(){
	glBegin(GL_POINTS);
	vector<Color>::iterator it = point_set.begin();
	for(int j=0 ;j<screenHeight; j++){
		for(int i=0; i<screenWidth; i++){
			glColor3f(it->red,it->green,it->blue);
			glVertex2i(i,j);
			it++;
		}
	}
	glEnd();
}

//zoom in 
void Mandelbrot::zoomIn(){
	if(minReal < maxReal - 2*realFactor) {
		 minReal = minReal + realFactor; 
		 maxReal = maxReal - realFactor;
	}
	
	scaleReal = (maxReal - minReal)/screenWidth;
	
	if(minImg < maxImg - 2*imgFactor) {
		minImg = minImg + imgFactor;
		maxImg = maxImg - imgFactor;
	}
	scaleImg = (maxImg - minImg)/screenHeight;
	
	//change the zoom factor affter zooming
	imgFactor = (maxReal - minReal)/40;
	realFactor = imgFactor*1.5;
	
	point_set.clear();
	createPointSet();
}

//zoom out
void Mandelbrot::zoomOut(){
	
	minReal = minReal - realFactor;
	maxReal = maxReal + realFactor;
	
	scaleReal = (maxReal - minReal)/screenWidth;

	minImg = minImg - imgFactor; 
	maxImg = maxImg + imgFactor;
	scaleImg = (maxImg - minImg)/screenHeight;
	
	//change the zoom factor after zooming
	imgFactor = (maxReal - minReal)/40;
	realFactor = imgFactor*1.5;
	
	point_set.clear();
	createPointSet();
}

// go to the left of the screen
void Mandelbrot::goLeft(){
	maxReal = maxReal - realFactor;
	minReal = minReal - realFactor;
	scaleReal = (maxReal - minReal)/screenWidth;
	point_set.clear();
	createPointSet();
}

// go to the right of the screen
void Mandelbrot::goRight(){
	maxReal = maxReal + realFactor;
	minReal = minReal + realFactor;
	scaleReal = (maxReal - minReal)/screenWidth;
	point_set.clear();
	createPointSet();
}

// go down
void Mandelbrot::goDown(){
	maxImg = maxImg - imgFactor;
	minImg = minImg - imgFactor;
	scaleImg = (maxImg - minImg) /screenHeight;
	point_set.clear();
	createPointSet();
}

// go up
void Mandelbrot::goUp(){
	maxImg = maxImg + imgFactor;
	minImg = minImg + imgFactor;
	scaleImg = (maxImg - minImg) /screenHeight;
	point_set.clear();
	createPointSet();
}
