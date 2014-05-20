#include <vector>
#include <iostream>
#include "Color.h"
#include "Complex.h"

using namespace std;
class Mandelbrot
{
	public:
		double minReal;
		double maxReal;
		double minImg;
		double maxImg;

		int screenWidth, screenHeight;
		float scaleReal;
		float scaleImg;
		int max_iteration;
		vector<Color> point_set;

	public:
		Mandelbrot(void);
		Mandelbrot(int the_screenWidth, int the_screenHeigh);
		~Mandelbrot(void);
		void draw();
		void zoomIn();
		void zoomOut();
		void goLeft();
		void goRight();
		void goUp();
		void goDown();
	private:
		void createPointSet();
};


