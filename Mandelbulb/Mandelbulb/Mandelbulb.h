/*
 * Mandelbulb.h
 *
 *  Created on: May 7, 2014
 *      Author: Leo
 */

#ifndef MANDELBULB_H_
#define MANDELBULB_H_
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <vector>
#include <math.h>
#include "Color.h"
#include "Vector3f.h"
#include "Complex.h"
#include <iostream>
using namespace std;

class Mandelbulb{
public:
	float minX, maxX;
	float minY, maxY;
	float minZ, maxZ;
	float xFactor, yFactor, zFactor;
	int xRange, yRange, zRange;
	int iteration;
	vector<Vector3f> points;
	vector<Color> ColorPoints;

	Vector3f currentPoint, nextPoint;
	double w, dw, theta, phi, distanceEstimator;
	int nOrder;
	int step;
	double thresholdDistance, bailout;
	//int count = 0;
public:
	Mandelbulb(int xRange, int yRange, int zRange, int iteration){
		this->xRange = xRange;
		this->yRange = yRange;
		this->zRange = zRange;
		this->iteration = iteration;
		minX = -1.5f; maxX = 1.5f;
		minY = -1.5f; maxY = 1.5f;
		minZ = -1.5f; maxZ = 1.5f;
		xFactor = (maxX-minX)/ xRange;
		yFactor = (maxY-minY)/ yRange;
		zFactor = (maxZ-minZ)/ zRange;
		initPoints();
	}
	void initPoints(){
		step = 100;
		thresholdDistance = 0.000001;
		nOrder = 8;
		bailout = 2.0;

		currentPoint.y = minY;
		for (int j = 0; j < yRange; j++){
			currentPoint.x = minX;
			for (int i = 0; i < xRange; i++){
				currentPoint.z = minZ;
				for (int k = step; k > 0 && currentPoint.z < maxZ; k--){
					nextPoint = currentPoint;
					dw = 1.0;
					w = 0.0;
					for (int iter = 0; iter < iteration; iter ++){
						if (w > bailout){
							break;
						}
						update();
					}
					distanceEstimator = 0.5*log(w)*w/dw;
					if (distanceEstimator < thresholdDistance){
						addPoint(k);
						break;
					}
					else{
						currentPoint.z += distanceEstimator;
					}
				}

				currentPoint.z = maxZ;
				for (int k = step; k > 0 && currentPoint.z > minZ; k--){
					nextPoint = currentPoint;
					dw = 1.0;
					w = 0.0;
					for (int iter = 0; iter < iteration; iter ++){
						if (w > bailout){
							break;
						}
						update();
					}
					distanceEstimator = 0.5*log(w)*w/dw;
					if (distanceEstimator < thresholdDistance){
						addPoint(k);
						break;
					}
					else{
						currentPoint.z -= distanceEstimator;
					}
				}
				currentPoint.x += xFactor;
			}
			currentPoint.y += yFactor;
		}

		currentPoint.x = minX;
		for (int j = 0; j < yRange; j++){
			currentPoint.z = minZ;
			for (int i = 0; i < xRange; i++){
				currentPoint.y = minY;
				for (int k = step; k > 0 && currentPoint.y < maxY; k--){
					nextPoint = currentPoint;
					dw = 1.0;
					w = 0.0;
					for (int iter = 0; iter < iteration; iter ++){
						if (w > bailout){
							break;
						}
						update();
					}
					distanceEstimator = 0.5*log(w)*w/dw;
					if (distanceEstimator < thresholdDistance){
						addPoint(k);
						break;
					}
					else{
						currentPoint.y += distanceEstimator;
					}
				}

				currentPoint.y = maxY;
				for (int k = step; k > 0 && currentPoint.y > minY; k--){
					nextPoint = currentPoint;
					dw = 1.0;
					w = 0.0;
					for (int iter = 0; iter < iteration; iter ++){
						if (w > bailout){
							break;
						}
						update();
					}
					distanceEstimator = 0.5*log(w)*w/dw;
					if (distanceEstimator < thresholdDistance){
						addPoint(k);
						break;
					}
					else{
						currentPoint.y -= distanceEstimator;
					}
				}
				currentPoint.z += zFactor;
			}
			currentPoint.x += xFactor;
		}

		currentPoint.z = minZ;
		for (int j = 0; j < yRange; j++){
			currentPoint.y = minY;
			for (int i = 0; i < xRange; i++){
				currentPoint.x = minX;
				for (int k = step; k > 0 && currentPoint.x < maxX; k--){
					nextPoint = currentPoint;
					dw = 1.0;
					w = 0.0;
					for (int iter = 0; iter < iteration; iter ++){
						if (w > bailout){
							break;
						}
						update();
					}
					distanceEstimator = 0.5*log(w)*w/dw;
					if (distanceEstimator < thresholdDistance){
						addPoint(k);
						break;
					}
					else{
						currentPoint.x += distanceEstimator;
					}
				}

				currentPoint.x = maxX;
				for (int k = step; k > 0 && currentPoint.x > minX; k--){
					nextPoint = currentPoint;
					dw = 1.0;
					w = 0.0;
					for (int iter = 0; iter < iteration; iter ++){
						if (w > bailout){
							break;
						}
						update();
					}
					distanceEstimator = 0.5*log(w)*w/dw;
					if (distanceEstimator < thresholdDistance){
						addPoint(k);
						break;
					}
					else{
						currentPoint.x -= distanceEstimator;
					}
				}
				currentPoint.y += xFactor;
			}
			currentPoint.z += yFactor;
		}
	}

	void update(){
		dw = dw*nOrder*pow(w,nOrder-1)+1;
		w = nextPoint.Length();
		int w8 = pow(w, nOrder);
		phi = atan(nextPoint.y/nextPoint.x)*nOrder;
		theta = acos(nextPoint.z/w)*nOrder;

		nextPoint.x = currentPoint.x + sin(theta)*cos(phi)*w8;
		nextPoint.y = currentPoint.y + sin(theta)*sin(phi)*w8;
		nextPoint.z = currentPoint.z + cos(theta)*w8;
	}

	void addPoint(int k){
		points.push_back(currentPoint);
		float RGBValue = float(k)/step;
		Color color(RGBValue, RGBValue, RGBValue);
		ColorPoints.push_back(color);
	}

	void draw(){
		glBegin(GL_POINTS);
		for (unsigned int i = 0; i < points.size(); i++){
			glColor3f(ColorPoints[i].red, ColorPoints[i].green, ColorPoints[i].blue);
			glVertex3f(points[i].x, points[i].y, points[i].z);
		}
		glEnd();
	}

};



#endif /* MANDELBULB_H_ */
