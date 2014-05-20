#include <vector>
#include <iostream>
#include "Color.h"
#include "Complex.h"

using namespace std;
class Mandelbrot
{
	public:
		double minReal;  // minimum value of real axis on the complex coordinate system
		double maxReal;  // maximum value of real axis on the complex coordinate system
		double minImg;   // minimum value of image axis on the complex coordinate system
		double maxImg;	// maximum value of image axis on the complex coordinate system

		int screenWidth, screenHeight;  // screen width and screen height
		float scaleReal;                // scale number on the real axis
		float scaleImg;									// scale number on the image axis
		int max_iteration;							// number of maximum iteration
		vector<Color> point_set;        // the set of color of pixels 
		
		double realFactor;							// the zoom factor on the real axis
		double imgFactor;               // the zoom factor on the image axis

	public:
		Mandelbrot(void);               // default construction
		Mandelbrot(int the_screenWidth, int the_screenHeigh); // construction with paremeters  
		~Mandelbrot(void);              // destruction
		void draw();										// draw function
		void zoomIn();									// zoom in
		void zoomOut();									// zoom out
		
		/*
		go to the left, the right, go up and go down
		*/
		void goLeft();					
		void goRight();
		void goUp();
		void goDown();
	private:
		void createPointSet();  // create set of color of points or pixels
};


