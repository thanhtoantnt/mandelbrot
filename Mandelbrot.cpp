
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>

#include "Mandelbrot.h"

const float realFactor = 0.045;
const float imgFactor = 0.03;
Mandelbrot::Mandelbrot(void){
}

Mandelbrot::Mandelbrot(int the_screenWidth, int the_screenHeight){
	minReal = -2.0; maxReal = 1.0;
	
	screenWidth = the_screenWidth; screenHeight = the_screenHeight;
	scaleReal = (maxReal - minReal)/screenWidth;

	minImg = -1.0; maxImg = 1.0;
	scaleImg = (maxImg - minImg)/ screenHeight;
 
	max_iteration = 32;
	createPointSet();	
}

Mandelbrot::~Mandelbrot(void){
}

void Mandelbrot::createPointSet(){
	int row, col, n;
	Complex c;
	Color color;
	
	c.img = minImg;
	for(row = 0; row < screenHeight; row++){
		c.real = minReal;
		for(col = 0; col < screenWidth; col++){
			Complex z(0,0);
			for(n = 0; n < max_iteration; n++){
				if(z.modulus() > 4){
					break;
				}
				z = z * z + c;
			}
		
			if(n < max_iteration) { 
				color =  Color::coloring(n, max_iteration);
			}
			
			else { color.red = color.green = color.blue = 0.0f; }
			point_set.push_back(color);
			
			c.real += scaleReal;
		}
		c.img += scaleImg;
	}
}

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
	
	point_set.clear();
	createPointSet();
}

void Mandelbrot::zoomOut(){
	
	minReal = minReal - realFactor;
	maxReal = maxReal + realFactor;
	
	scaleReal = (maxReal - minReal)/screenWidth;

	minImg = minImg - imgFactor; 
	maxImg = maxImg + imgFactor;
	scaleImg = (maxImg - minImg)/screenHeight;
	
	point_set.clear();
	createPointSet();
}

void Mandelbrot::goLeft(){
	maxReal = maxReal - realFactor;
	minReal = minReal - realFactor;
	scaleReal = (maxReal - minReal)/screenWidth;
	point_set.clear();
	createPointSet();
}

void Mandelbrot::goRight(){
	maxReal = maxReal + realFactor;
	minReal = minReal + realFactor;
	scaleReal = (maxReal - minReal)/screenWidth;
	point_set.clear();
	createPointSet();
}

void Mandelbrot::goDown(){
	maxImg = maxImg - imgFactor;
	minImg = minImg - imgFactor;
	scaleImg = (maxImg - minImg) /screenHeight;
	point_set.clear();
	createPointSet();
}

void Mandelbrot::goUp(){
	maxImg = maxImg + imgFactor;
	minImg = minImg + imgFactor;
	scaleImg = (maxImg - minImg) /screenHeight;
	point_set.clear();
	createPointSet();
}




