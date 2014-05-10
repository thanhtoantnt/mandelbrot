/*
 * Colour.h
 *
 *  Created on: May 6, 2014
 *      Author: Leo
 */

#ifndef COLOUR_H_
#define COLOUR_H_
#include <math.h>
struct Color{
	float red,green,blue;

	Color(float red, float green, float blue){
		this->red = red; this->green = green; this->blue = blue;
	}
	void set(float red, float green, float blue){
		this->red = red; this->green = green; this->blue = blue;
	}
	static Color HueToRGB(float hue){
		hue = fmodf(hue,360.0f);
		Color color(0.0f,0.0f,0.0f);

		float h = hue/60;
		float x = (1 - fabs(fmodf(h, 2) - 1));
		float s = 1.0f;
		float v = 1.0f;
		float c = v*s;
		float z = 0.0f;
		switch((int)floor(h)){
			case 0:
				color.set(c, x, z);
				break;
			case 1:
				color.set(x, c, z);
				break;
			case 2:
				color.set(z, c, x);
				break;
			case 3:
				color.set(z, x, c);
				break;
			case 4:
				color.set(x, z, c);
				break;
			case 5:
				color.set(c, z, x);
				break;
			default:
				color.set(z, z, z);
				break;
		}
		return color;
	}
};



#endif /* COLOUR_H_ */
