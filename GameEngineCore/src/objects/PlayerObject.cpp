#include "PlayerObject.h"

namespace spacey{
	namespace objects{
		PlayerObject::PlayerObject(Window* window, Motion* motion, string filename, int tWidth, int tHeight){
			x_coord = 0;
			y_coord = 0;
			m_texWidth = tWidth;
			m_texHeight = tHeight;
			m_window = window;
			motionObj = motion;
			start = clock();
			delay = clock();
			healthStart = clock();

			inven.Init(window, "Resources/Images/Inventory.png");

			if (filename != "")
				imageLoaded = loadAnimateable(filename, m_image, u2, v2, width, height);

			framesPerRow = width / m_texWidth;//Important to use raw width because u2 is a modified size
		}

		void PlayerObject::AI(string indicator){
			//Set the BaseEntity's version of the animFlag to the players, only because there is a separate one
			mObj.animFlag = motionObj->animFlag; 
			
			inven.open = openInven();
			inven.update();

			checkRotation(motionObj);
			checkFire();
			regenHealth();

			if (!shot.empty()){
				for (int i = 0; i < shot.size(); i++){
					shot[i].Fire();
					if (shot[i].limit()){
						shot.erase(shot.begin() + i);
					}
				}
			}

			/*if (inven.render.joinable()){
				inven.render.join();
			}*/
		}

		bool PlayerObject::openInven(){
			if (m_window->isKeyPressed(GLFW_KEY_I)){

				if (tick >= MINIMUM_INVEN_TICK){
					tick = 0;

					if (inven.open){
						return false;
					}
					else{
						return true;
					}
				}
				else{
					tick++;
					return inven.open;
				}
			}
			
			return inven.open;
		}

		void PlayerObject::checkRotation(Motion* motion){
			direction = motion->angle;

			if (direction == 0){
				direction = 1;
			}
			else if (direction == 45){
				direction = 2;
			}
			else if (direction == 90){
				direction = 3;
			}
			else if (direction == 135){
				direction = 4;
			}
			else if (direction == 180){
				direction = 5;
			}
			else if (direction == 225){
				direction = 6;
			}
			else if (direction == 270){
				direction = 7;
			}
			else if (direction == 315){
				direction = 8;
			}
		}

		void PlayerObject::checkFire(){
			if (m_window->isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)){
				if (shotLast <= waited){
					Bullet bullet(direction, x_coord, y_coord);
					shot.push_back(bullet);
					waited = 0;
					delay = clock();
				}
				else
				{
					waited = (clock() - delay) / CLOCKS_PER_SEC;
					cout << "Can't shoot yet.\n";
				}
			}
		}

		void PlayerObject::takeDamage(int amount){

			if (passed >= wait){
				//Removing Health
				health -= amount;
				cout << "Player now has " << health << " health left.\n";

				//Resetting the timer
				passed = 0;
				start = clock();
			}
			else{
				passed = (clock() - start) / CLOCKS_PER_SEC;
				cout << "Could not remove damage yet.\n";
			}
		}
		
		void PlayerObject::regenHealth(){
			if (health < 100 && healthPassed > healthWait){
				//Regens the players health when its less than 100.
				//Created by Kenneth Morgridge
				healthPassed = 0;
				healthStart = clock();
				health = health + 10;
				cout << "10 health restored." << endl;
				cout << "health is now " << health << endl;
			}
			else{
				healthPassed = (clock() - healthStart) / CLOCKS_PER_SEC;
			}

			}
		}

	}
