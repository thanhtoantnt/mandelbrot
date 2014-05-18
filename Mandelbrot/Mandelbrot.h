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
		float zoom_factor;
		int iteration;
		vector<Color> points;

	public:
		Mandelbrot(void);
		Mandelbrot(int _screenWidth, int _screenHeigh);
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


