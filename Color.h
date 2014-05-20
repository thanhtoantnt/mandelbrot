
#include <math.h>
struct Color{
	float red,green,blue;

	Color(){}
	Color(float the_red, float the_green, float the_blue){
		red = the_red; green = the_green; blue = the_blue;
	}

	static Color coloring(int iteration, int max_iteration){
		Color color(0.0f, 0.0f, 0.0f);
		color.red = color.green = color.blue = (double)iteration/max_iteration;
		return color;
	}
};
