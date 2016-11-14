#include "MotionController.h"

namespace spacey{ namespace motion{

	void Motion::dirRight(){
		xspeed = speed;
		animFlag = "WALK_RIGHT";
	}

	void Motion::dirLeft(){
		xspeed = -speed;
		animFlag = "WALK_LEFT";
	}

	void Motion::dirUp(){
		yspeed = speed;
		animFlag = "WALK_UP";
	}

	void Motion::dirDown(){
		yspeed = -speed;
		animFlag = "WALK_DOWN";
	}

	void Motion::rotateLeft(int IN){

		if (IN == NULL){
			angle -= angleIncriment;
		}
		else{
			angle -= IN;
		}

		//Angle resetting to stay within 360 degrees
		while (angle >= 360){
			angle -= 360;
		}
		while (angle < 0){
			angle += 360;
		}
	}

	void Motion::rotateRight(int IN){
		
		if (IN == NULL){
			angle += angleIncriment;
		}
		else{
			angle += IN;
		}

		//Angle resetting to stay within 360 degrees
		while (angle >= 360){
			angle -= 360;
		}
		while (angle < 0){
			angle += 360;
		}
	}

	void Motion::applySpeed(){
		// use -= to move background opposite to input
		xspeed = -xspeed;
		yspeed = -yspeed;

	}

	void Motion::applyRotation(float x, float y){

		glTranslatef(x, y, 0);
		glRotatef(-angle, 0, 0, 1);
		glTranslatef(-x, -y, 0);
	}
} }