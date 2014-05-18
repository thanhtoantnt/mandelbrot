/*
 * Vector3f.h
 *
 *  Created on: May 7, 2014
 *      Author: Leo
 */

#ifndef VECTOR3F_H_
#define VECTOR3F_H_
#include <math.h>
#include <iostream>
using namespace std;

struct Vector3f
{
	float x,y,z;
	Vector3f(){

	}
	Vector3f(float x,float y,float z){
		this->x = x;
		this->y = y;
		this->z = z;
	}
	void Normalize(){
		double ratio = 1/Length();
		this->x *= (float)ratio;
		this->y *= (float)ratio;
		this->z *= (float)ratio;
	}
	inline double Length(){
		return sqrt(x*x + y*y + z*z);
	}

	Vector3f operator + ( const Vector3f & rhs ) const {
		return( Vector3f( x + rhs.x, y + rhs.y, z + rhs.z ) );
	}

	Vector3f operator - (const Vector3f & rhs) const{
		return( Vector3f( x - rhs.x, y - rhs.y, z - rhs.z ) );
	}

	Vector3f operator * (float k) const{
		return( Vector3f( x * k, y * k, z * k ) );
	}
	void operator = (const Vector3f & rhs){
		x = rhs.x; y = rhs.y; z = rhs.z;
	}
	bool operator == (const Vector3f &rhs){
		return (x == rhs.x && y == rhs.y && z == rhs.z);
	}

	static float dot(Vector3f & lhs, Vector3f & rhs){
		return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
	}
	static Vector3f cross(const Vector3f & lhs, const Vector3f & rhs ) {
		return( Vector3f( lhs.y * rhs.z - lhs.z * rhs.y,
						  lhs.z * rhs.x - lhs.x * rhs.z,
					      lhs.x * rhs.y - lhs.y * rhs.x ) );
	}
	void printOut(){
		cout<<"("<<x<<","<<y<<","<<z<<")"<<endl;
	}
};



#endif /* VECTOR3F_H_ */
