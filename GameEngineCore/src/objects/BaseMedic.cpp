//Made by Kenny and Will
#include "BaseMedic.h"

namespace spacey{
	namespace objects{

		BaseMedic::BaseMedic(){
			x_coord = 0;
			y_coord = 0;
		}

		BaseMedic::~BaseMedic(){

		}

		BaseMedic::BaseMedic(int x, int y, int tWidth, int tHeight, string filename){
			x_coord = x;
			y_coord = y;
			m_texWidth = tWidth;
			m_texHeight = tHeight;
			imageLoaded = loadAnimateable(filename, m_image, u2, v2, width, height);

			framesPerRow = width / m_texWidth;
		}

		void BaseMedic::AI(string indicator){
			if (indicator == "REDIRECT"){
				direction++;

				if (direction > 8)
					direction = 1;

				steps = 0;
			}
			else if (indicator == "RETREAT"){
				AI_Flag = indicator;

			}
			else if (indicator == "IDLE"){
				AI_Flag = indicator;
				move();
			}
		}

		void BaseMedic::Heal(BaseEntity* enem, unsigned int i, string type){

			if (enem->health <= 50 && healing == i && healType == type){
				available = false;

				if (enem->x_coord > x_coord){
					x_coord++;
				} 

				if (enem->x_coord < x_coord){
					x_coord--;
				}
				
				if (enem->y_coord > y_coord){
					y_coord++;
				}
				
				if (enem->y_coord < y_coord){
					y_coord--;
				}

				if ((x_coord - (m_width / 2) <= enem->x_coord + (enem->m_width / 2) && x_coord + (m_width / 2) >= enem->x_coord - (enem->m_width / 2)
					&& y_coord + (m_height / 2) >= enem->y_coord - (enem->m_height / 2) && y_coord - (m_height / 2) <= enem->y_coord - (enem->m_height / 2))){
					enem->health += 10;

					if (enem->health > 50){
						available = true;
						healType = "";
					}
					cout << "Enemy has been healed 10 single points" << endl;
					cout << "Current Health: " << enem->health << endl;
					cout << "Y U DO ANAL?" << endl;
				}
			}
			else if (enem->health <= 50 && available == true){
				healing = i;
				healType = type;
			}

		}

		void BaseMedic::move(){
			if (steps >= STEP_MAX){
				steps = 0;
				direction = rand() % 8 + 1;
			}
			else{
				switch (direction){
				case 1: //Up
					y_coord += 0.2;
					mObj.animFlag = "WALK_UP";
					break;
				case 2: //Up Right
					x_coord += 0.2;
					y_coord += 0.2;
					break;
				case 3:  //Right
					x_coord += 0.2;
					mObj.animFlag = "WALK_RIGHT";
					break;
				case 4: //Down Right
					x_coord += 0.2;
					y_coord -= 0.2;
					break;
				case 5: //Down
					y_coord -= 0.2;
					mObj.animFlag = "WALK_DOWN";
					break;
				case 6: //Left Down
					x_coord -= 0.2;
					y_coord -= 0.2;
					break;
				case 7: //Left
					x_coord -= 0.2;
					mObj.animFlag = "WALK_LEFT";
					break;
				case 8: //Left Up
					x_coord -= 0.2;
					y_coord += 0.2;
					break;
				default:
					std::cout << "Not a valid enemy movement key.\n";
					break;
				}

				steps++;
			}
		}

		BaseMedic BaseMedic::operator=(BaseMedic right){
			right.AI_Flag = AI_Flag;
			right.available = available;
			right.counter = counter;
			right.currentFrame = currentFrame;
			right.direction = direction;
			right.framesPerRow = framesPerRow;
			right.healing = healing;
			right.health = health;
			right.healType = healType;
			right.height = height;
			right.imageLoaded = imageLoaded;
			right.m_height = m_height;
			right.m_image = m_image;
			right.m_texHeight = m_texHeight;
			right.m_texWidth = m_texWidth;
			right.m_width = m_width;
			right.pointing = pointing;
			right.steps = steps;
			right.u2 = u2;
			right.v2 = v2;
			right.width = width;
			right.u3 = u3;
			right.v3 = v3;
			right.x_coord = x_coord;
			right.y_coord = y_coord;

			return right;
		}
	}
}