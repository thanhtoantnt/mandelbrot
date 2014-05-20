/*
 * Camera.h
 *
 *  Created on: May 13, 2014
 *      Author: Leo
 */

#ifndef CAMERA_H_
#define CAMERA_H_
#define _USE_MATH_DEFINES

#include <windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>
#include <math.h>
#include "Vector3f.h"

class Camera{
public:
		Vector3f eye;
		Vector3f u,v,n;
		float aspect, nearDistance, farDistance, viewAngle, W, H;
		int nRow, nColumn;
public:
		Camera(){
		}

		void setDefaultCamera(){
			setPerspective(75.0f, 640/(float)480, 0.1f, 200.0f); // good default values here
			setLookAt(Vector3f(100, 100, 100), Vector3f(0, 0, 0), Vector3f(0, 1, 0));
		}
		void setDisplay(int nRow, int nColumn){
			this->nRow = nRow;
			this->nColumn = nColumn;
		}

		void setLookAt(Vector3f eye, Vector3f look, Vector3f up){
			this->eye = eye;
			this->n = Vector3f(eye.x - look.x , eye.y - look.y , eye.z - look.z);
			this->u = Vector3f::cross(up,n);
			this->v = Vector3f::cross(n,u);
			n.Normalize();
			u.Normalize();
			v.Normalize();
			setModelViewMatrix();
		}

		void setLookAt(float eye_x,float eye_y,float eye_z, float look_x, float look_y, float look_z, float up_x, float up_y, float up_z){
			setLookAt(Vector3f(eye_x,eye_y,eye_z),Vector3f(look_x,look_y,look_z),Vector3f(up_x,up_y,up_z));
		}		
		void setPerspective(float viewAngle, float aspect, float nearDistance, float farDistance){
			this->viewAngle = viewAngle;
			this->aspect = aspect;
			this->nearDistance = nearDistance; 
			this->farDistance = farDistance;
			this->H = nearDistance * tan(M_PI * viewAngle/(2.0 * 180));
			this->W = aspect * H;
			setProjectionMatrix();
		}

		void roll(float angle){
			rotateAxes(u,v,-angle);
		}
		
		void yaw(float angle){
			rotateAxes(n,u,-angle);
		}
		void pitch(float angle){
			rotateAxes(n,v,-angle);
		}
		void slide(float du,float dv, float dn){
			eye.x += du * u.x + dv * v.x + dn * n.x;
			eye.y += du * u.y + dv * v.y + dn * n.y;
			eye.z += du * u.z + dv * v.z + dn * n.z;
			setModelViewMatrix();
		}

		void rotateAxes(Vector3f &a, Vector3f &b, float angle){
			float radianAngle = M_PI/180 * angle;
			float cosVal = cos(radianAngle);
			float sinVal = sin(radianAngle);
			Vector3f newA(cosVal * a.x + sinVal * b.x, cosVal * a.y + sinVal * b.y, cosVal * a.z + sinVal * b.z);
			Vector3f newB(-sinVal * a.x + cosVal * b.x, -sinVal * a.y + cosVal * b.y, -sinVal * a.z + cosVal * b.z);
			a = newA; b = newB;
			setModelViewMatrix();
		}
		void setModelViewMatrix(){
			float matrix[16];
			Vector3f eyeVector(eye.x,eye.y,eye.z);
			matrix[0] = u.x ; matrix[4] = u.y ; matrix[8] = u.z ; matrix[12] = -Vector3f::dot(eyeVector,u);
			matrix[1] = v.x ; matrix[5] = v.y ; matrix[9] = v.z ; matrix[13] = -Vector3f::dot(eyeVector,v);
			matrix[2] = n.x ; matrix[6] = n.y ; matrix[10]= n.z ; matrix[14] = -Vector3f::dot(eyeVector,n);
			matrix[3] = 0	; matrix[7] = 0	  ; matrix[11] = 0	; matrix[15] = 1;
			glMatrixMode(GL_MODELVIEW);
			glLoadMatrixf(matrix);
		}

		void setProjectionMatrix(){
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(viewAngle,aspect,nearDistance,farDistance);
			glMatrixMode(GL_MODELVIEW);
		}
};


#endif /* CAMERA_H_ */
