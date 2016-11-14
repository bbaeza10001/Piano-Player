#include "InputController.h"

namespace spacey{ namespace input{

	void checkForInput(Window* window, Motion* motionObj, BG &bckgrnd){
		int colCode = bckgrnd.testCollision();

		//Horizontal Movement
		if (window->isKeyPressed(GLFW_KEY_D) && !window->isKeyPressed(GLFW_KEY_W) 
			&& !window->isKeyPressed(GLFW_KEY_S)){

			if (colCode != 2){
				motionObj->dirRight();
			}
			else{
				motionObj->xspeed = 0;
			}

			//Turning the player to point where they are going
			if (motionObj->angle != 90){
				if (motionObj->angle >= 270 || motionObj->angle < 90){
					motionObj->rotateRight(NULL);
				}
				else if (motionObj->angle < 270 && motionObj->angle > 90){
					motionObj->rotateLeft(NULL);
				}
			}
		}
		else if (window->isKeyPressed(GLFW_KEY_A) && !window->isKeyPressed(GLFW_KEY_W)
			&& !window->isKeyPressed(GLFW_KEY_S)){

			if (colCode != 1){
				motionObj->dirLeft();
			}
			else{
				motionObj->xspeed = 0;
			}

			//Turning the player to point where they are going
			if (motionObj->angle != 270){
				if (motionObj->angle > 270 || motionObj->angle <= 90){
					motionObj->rotateLeft(NULL);
				}
				else if (motionObj->angle < 270 && motionObj->angle > 90){
					motionObj->rotateRight(NULL);
				}
			}

		}

		//Vertical Movement
		if (window->isKeyPressed(GLFW_KEY_W) && !window->isKeyPressed(GLFW_KEY_A)
			&& !window->isKeyPressed(GLFW_KEY_D)){

			if (colCode != 3){
				motionObj->dirUp();
			}
			else{
				motionObj->yspeed = 0;
			}

			//Turning the player to point where they are going
			if (motionObj->angle != 0){
				if (motionObj->angle >= 180){
					motionObj->rotateRight(NULL);
				}
				else if (motionObj->angle < 180){
					motionObj->rotateLeft(NULL);
				}
			}
		} 
		else if (window->isKeyPressed(GLFW_KEY_S) && !window->isKeyPressed(GLFW_KEY_A)
			&& !window->isKeyPressed(GLFW_KEY_D)){

			if (colCode != 4){
				motionObj->dirDown();
			}
			else{
				motionObj->yspeed = 0;
			}

			//Turning the player to point where they are going
			if (motionObj->angle != 180){
				if (motionObj->angle < 180){
					motionObj->rotateRight(NULL);
				}
				else if (motionObj->angle > 180){
					motionObj->rotateLeft(NULL);
				}
			}

		}

		//Checking if moving at an angle and turns/moves player accordingly
		if (window->isKeyPressed(GLFW_KEY_W) && window->isKeyPressed(GLFW_KEY_D)){
			
			if (colCode != 2 && colCode != 3){
				motionObj->dirRight();
				motionObj->dirUp();
			}
			else{
				motionObj->xspeed = 0;
				motionObj->yspeed = 0;
			}

			if (motionObj->angle != 45){
				if (motionObj->angle >= 225 || motionObj->angle < 45){
					motionObj->rotateRight(NULL);
				}
				else if (motionObj->angle < 225 && motionObj->angle > 45){
					motionObj->rotateLeft(NULL);
				}
			}
		}
		else if (window->isKeyPressed(GLFW_KEY_W) && window->isKeyPressed(GLFW_KEY_A)){

			if (colCode != 1 && colCode != 3){
				motionObj->dirLeft();
				motionObj->dirUp();
			}
			else{
				motionObj->xspeed = 0;
				motionObj->yspeed = 0;
			}

			if (motionObj->angle != 315){
				if (motionObj->angle >= 135 && motionObj->angle < 315){
					motionObj->rotateRight(NULL);
				}
				else if (motionObj->angle < 135 || motionObj->angle > 315){
					motionObj->rotateLeft(NULL);
				}
			}
		}
		else if (window->isKeyPressed(GLFW_KEY_S) && window->isKeyPressed(GLFW_KEY_D)){

			if (colCode != 2 && colCode != 4){
				motionObj->dirRight();
				motionObj->dirDown();
			}
			else{
				motionObj->xspeed = 0;
				motionObj->yspeed = 0;
			}

			if (motionObj->angle != 135){
				if (motionObj->angle >= 315 || motionObj->angle < 135){
					motionObj->rotateRight(NULL);
				}
				else if (motionObj->angle > 135 && motionObj->angle < 315){
					motionObj->rotateLeft(NULL);
				}
			}
		}
		else if (window->isKeyPressed(GLFW_KEY_S) && window->isKeyPressed(GLFW_KEY_A)){
			
			if (colCode != 1 && colCode != 4){
				motionObj->dirLeft();
				motionObj->dirDown();
			}
			else{
				motionObj->xspeed = 0;
				motionObj->yspeed = 0;
			}

			if (motionObj->angle != 225){
				if (motionObj->angle >= 45 && motionObj->angle < 225){
					motionObj->rotateRight(NULL);
				}
				else if (motionObj->angle > 225 || motionObj->angle < 45){
					motionObj->rotateLeft(NULL);
				}
			}
		}

		//Things being done once nothing is being pressed
		if (!window->isKeyPressed(GLFW_KEY_D) && !window->isKeyPressed(GLFW_KEY_A) &&
			!window->isKeyPressed(GLFW_KEY_W) && !window->isKeyPressed(GLFW_KEY_S)){

			//Stopping the player
			motionObj->xspeed = 0;
			motionObj->yspeed = 0;
			
			//Return to idle animation
			motionObj->animFlag = "IDLE";
		}

		
	}

} }