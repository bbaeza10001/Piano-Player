#include "BaseEnemy.h"

namespace spacey{ namespace objects{

	BaseEnemy::BaseEnemy(){
		x_coord = 0;
		y_coord = 0;
	}

	BaseEnemy::BaseEnemy(int x, int y, int tWidth, int tHeight, string filename){
		x_coord = x;
		y_coord = y;
		m_texWidth = tWidth;
		m_texHeight = tHeight;
		imageLoaded = loadAnimateable(filename, m_image, u2, v2, width, height);

		framesPerRow = width / m_texWidth;
	}

	BaseEnemy::~BaseEnemy(){
		
	}

	void BaseEnemy::AI(string indicator){

		if (indicator == "REDIRECT"){
			direction++;

			if (direction > 8)
				direction = 1;

			steps = 0;
		}
		else if (indicator == "ATTACK"){
			pursue();
		}
		else if (indicator == "RETREAT"){
			flee();
		}
		else if (indicator == "IDLE"){
			walk();
		}

		if (!delaware.empty()){
			for (int i = 0; i < delaware.size(); i++){
				delaware[i].Fire();
				if (delaware[i].limit()){
					delaware.erase(delaware.begin() + i);
				}
			}
		}
	}
	
	void BaseEnemy::bulletFill(){
		Bullet bullet(direction, x_coord, y_coord);
		delaware.push_back(bullet);
	}

	void BaseEnemy::createNewBullet(){
		if (counter < 500){
			counter++;
		}
		else{
			bulletFill();
			counter = 0;
		}
	}

	void BaseEnemy::walk(){
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

	void BaseEnemy::flee(){

		//Move in the correct x direction
		if (p_x > x_coord){
			x_coord -= 0.2;
		}
		else if (p_x < x_coord){
			x_coord += 0.2;
		}

		//Move in the correct y direction
		if (p_y > y_coord){
			y_coord -= 0.2;
		}
		else if (p_y < y_coord){
			y_coord += 0.2;
		}

		
	}

	void BaseEnemy::pursue(){

		if (health >= 20){

			//Move in the correct x direction
			if (p_x > x_coord){
				x_coord += 0.2;
			}
			else if (p_x < x_coord){
				x_coord -= 0.2;
			}

			//Move in the correct y direction
			if (p_y > y_coord){
				y_coord += 0.2;
			}
			else if (p_y < y_coord){
				y_coord -= 0.2;
			}

			//Once the enemy is lined up with the player, shoot
			if (x_coord - (m_width / 2) <= 16 && x_coord + (m_width / 2) >= -16){
				createNewBullet();
			}

			if (y_coord + (m_height / 2) >= -16 && y_coord - (m_height / 2) <= 16){
				createNewBullet();
			}
		}
	}

	bool BaseEnemy::checkArea(PlayerObject player){
		
		//If the player is within a 100 pixel radius of the enemy...
		if (x_coord <= 100 && x_coord >= -100
			&& y_coord >= -100 && y_coord <= 100){

			//Return true and save it's coordinates and health
			p_x = player.x_coord;
			p_y = player.y_coord;
			p_health = player.health;

			return true;
		}

		return false;
	}

	BaseEnemy BaseEnemy::operator=(BaseEnemy right){

		BaseEnemy temp;

		temp.bX = right.bX;
		temp.bY = right.bY;
		temp.counter = right.counter;
		temp.delaware = right.delaware;
		temp.direction = right.direction;
		temp.health = right.health;
		temp.height = right.height;
		temp.imageLoaded = right.imageLoaded;
		temp.m_image = right.m_image;
		temp.pointing = right.pointing;
		temp.steps = right.steps;
		temp.u2 = right.u2;
		temp.u3 = right.u3;
		temp.v2 = right.v2;
		temp.v3 = right.v3;
		temp.width = right.width;
		temp.x_coord = right.x_coord;
		temp.y_coord = right.y_coord;

		return temp;
	}
} }