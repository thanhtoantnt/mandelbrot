

#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>

#include "Mandelbrot.h"

const float realFactor = 0.04;
const float imgFactor = 0.03;
Mandelbrot::Mandelbrot(void)
{
}

Mandelbrot::Mandelbrot(int _screenWidth, int _screenHeight){
	minReal = -2.0; maxReal = 1.0;
	
	screenWidth = _screenWidth; screenHeight = _screenHeight;
	scaleReal = (maxReal - minReal)/screenWidth;

	minImg = -1.3; maxImg = 1.3;
	scaleImg = (maxImg - minImg)/ screenHeight;
 
	iteration = 32;
	cout<<"Initial iteration: "<<iteration<<endl;
	zoom_factor = 1.0f;

	createPointSet();	
	//isChanged = true;
}

Mandelbrot::~Mandelbrot(void)
{
}

void Mandelbrot::createPointSet(){
	int row, col, n;
	Complex c, z;

	Color color;
	double log2 = log(2.0);
	double smooth_value;

	c.img = minImg;
	for(row = 0; row < screenHeight; row++){
		c.real = minReal;
		for(col = 0; col < screenWidth; col++){
			z.real = 0; z.img = 0;
			//Vong lap kiem tra 1 diem co thuoc Mandelbrot set khong
			for(n = 0; n < iteration; n++){
				if(z.DistanceSquare() > 4){
					break;
				}
				z = z * z + c;
			}
			
			//Neu khong thuoc set
			if(n < iteration) { 
				smooth_value = (n + 1 - log(log(z.DistanceSquare())/log(2))/log2)/iteration;
				color =  Color::HueToRGB(smooth_value*360);
			}
			//Neu thuoc set thi cho mau den
			else { color.red = color.green = color.blue = 0.0f; }
			points.push_back(color);
			
			c.real += scaleReal;
		}
		c.img += scaleImg;
	}
}

void Mandelbrot::draw(){
	glBegin(GL_POINTS);
	vector<Color>::iterator it = points.begin();
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
	
	points.clear();
	createPointSet();
}

void Mandelbrot::zoomOut(){
	
	minReal = minReal - realFactor;
	maxReal = maxReal + realFactor;
	
	scaleReal = (maxReal - minReal)/screenWidth;

	minImg = minImg - imgFactor; 
	maxImg = maxImg + imgFactor;
	scaleImg = (maxImg - minImg)/screenHeight;
	
	points.clear();
	createPointSet();
}

void Mandelbrot::goLeft(){
	maxReal = maxReal - realFactor;
	minReal = minReal - realFactor;
	scaleReal = (maxReal - minReal)/screenWidth;
	points.clear();
	createPointSet();
}

void Mandelbrot::goRight(){
	maxReal = maxReal + realFactor;
	minReal = minReal + realFactor;
	scaleReal = (maxReal - minReal)/screenWidth;
	points.clear();
	createPointSet();
}

void Mandelbrot::goDown(){
	maxImg = maxImg - imgFactor;
	minImg = minImg - imgFactor;
	scaleImg = (maxImg - minImg) /screenHeight;
	points.clear();
	createPointSet();
}

void Mandelbrot::goUp(){
	maxImg = maxImg + imgFactor;
	minImg = minImg + imgFactor;
	scaleImg = (maxImg - minImg) /screenHeight;
	points.clear();
	createPointSet();
}




