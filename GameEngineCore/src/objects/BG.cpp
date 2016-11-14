#include "BG.h"

namespace spacey{
	namespace background{
	
		BG::BG(){
			
		}

		BG::BG(Window* window){
			m_window = window;
		}

		void BG::loadFile(string filename, string type){

			if (type == "ENTITY"){
				loadEntity(entities, filename);
			}
			else if (type == "ENVIRONMENT"){
				loadObject(environment, filename);
			}
			cout << "Elements added to BG Buffer\n";
		}

		void BG::update(Motion* motion, PlayerObject* player){
			motion->applySpeed();
			move(motion, player);
			checkBullets(player);

			/*for (unsigned int i = 0; i < B_Enemy.size(); i++){
				if (B_Enemy[i].x_coord < 800 && B_Enemy[i].x_coord > -800){
					if (B_Enemy[i].y_coord < 600 && B_Enemy[i].y_coord > -600){
						B_Enemy[i].Draw();
						if (B_Enemy[i].checkArea(*player))
							B_Enemy[i].AI("ATTACK");
					}
				}
			}
			for (unsigned int i = 0; i < B_Medics.size(); i++){
				if (B_Medics[i].x_coord < 800 && B_Medics[i].x_coord > -800){
					if (B_Medics[i].y_coord < 600 && B_Medics[i].y_coord > -600){
						B_Medics[i].Draw();
					}
				}
			}
			for (unsigned int i = 0; i < Ml_Enemy.size(); i++){
				if (Ml_Enemy[i].x_coord < 800 && Ml_Enemy[i].x_coord > -800){
					if (Ml_Enemy[i].y_coord < 600 && Ml_Enemy[i].y_coord > -600){
						Ml_Enemy[i].Draw();
					}
				}
			}

			for (unsigned int i = 0; i < walls.size(); i++){
				if (walls[i].x_coord < 800 && walls[i].x_coord > -800){
					if (walls[i].y_coord < 600 && walls[i].y_coord > -600){
						walls[i].Draw();
					}
				}
			}

			for (unsigned int i = 0; i < doors.size(); i++){
				if (doors[i].x_coord < 800 && doors[i].x_coord > -800){
					if (doors[i].y_coord < 600 && doors[i].y_coord > -600){
						doors[i].draw(m_window);
					}
				}
			}*/

			for (unsigned int i = 0; i < environment.size(); i++){
				if (environment[i].x_coord < 800 && environment[i].x_coord > -800){
					if (environment[i].y_coord < 600 && environment[i].y_coord > -600){
						environment[i].Draw();
					}
				}
			}

			for (unsigned int i = 0; i < entities.size(); i++){
				if (entities[i]->x_coord < 800 && entities[i]->x_coord > -800){
					if (entities[i]->y_coord < 600 && entities[i]->y_coord > -600){
						entities[i]->Draw();
					}
				}
			}

			

			//Don't forget to add AI calls to Base Enemy to check if the player is nearby

		}

		void BG::move(Motion* motion, PlayerObject* player){
			
			for (unsigned int i = 0; i < player->shot.size(); i++){
				player->shot[i].bX += motion->xspeed;
				player->shot[i].bY += motion->yspeed;
			}

			for (unsigned int i = 0; i < entities.size(); i++){
				entities[i]->x_coord += motion->xspeed;
				entities[i]->y_coord += motion->yspeed;
			}
			
			for (unsigned int i = 0; i < environment.size(); i++){
				environment[i].x_coord += motion->xspeed;
				environment[i].y_coord += motion->yspeed;
			}

			//Update bullet movements for Base Enemy
		}

		void BG::checkBullets(PlayerObject* player){
			for (unsigned int i = 0; i < B_Enemy.size(); i++){ //For every basic enemy in world
				

				//Basic enemy -> player
				for (unsigned int c = 0; c < B_Enemy[i].delaware.size(); c++){ //
					if (B_Enemy[i].delaware[c].bX >= -15 && B_Enemy[i].delaware[c].bX <= 15){ //The X coordinateCheck their bullet vectors to see if...s
						if (B_Enemy[i].delaware[c].bY >= -15 && B_Enemy[i].delaware[c].bY <= 15){//and Y coordinates are the same as the players region

							//If so, delete the bullet that collided, and remove health from the player
							B_Enemy[i].delaware.erase(B_Enemy[i].delaware.begin() + c);
							player->takeDamage(10);
						}
					}
				}


				//Player -> basic enemy
				for (unsigned int c = 0; c < player->shot.size(); c++){
					if (player->shot[c].bX >= B_Enemy[i].x_coord - 16 && player->shot[c].bX <= B_Enemy[i].x_coord + 16){
						if (player->shot[c].bY >= B_Enemy[i].y_coord - 16 && player->shot[c].bY <= B_Enemy[i].y_coord + 16){

							player->shot.erase(player->shot.begin() + c);
							B_Enemy[i].health -= 10;
							cout << "Enemy now has " << B_Enemy[i].health << " hp\n";
						}
					}
				}
				//Death function. Created by Kenneth.
				for (unsigned int g = 0; g < entities.size(); g++){
					if (entities[g]->health <= 0){
						entities.erase(entities.begin() + g);
					}
				}
			}

			//Player -> melee enemy 
			for (unsigned int i = 0; i < Ml_Enemy.size(); i++){
				for (unsigned int c = 0; c < player->shot.size(); c++){
					if (player->shot[c].bX >= Ml_Enemy[i].x_coord - 16 && player->shot[c].bX <= Ml_Enemy[i].x_coord + 16){
						if (player->shot[c].bY >= Ml_Enemy[i].y_coord - 16 && player->shot[c].bY <= Ml_Enemy[i].y_coord + 16){

							player->shot.erase(player->shot.begin() + c);
							Ml_Enemy[i].health -= 10;
							cout << "Enemy now has " << Ml_Enemy[i].health << " hp\n";
						}
					}
				}
			}

			for (unsigned int i = 0; i < Ml_Enemy.size(); i++){ //For every melee enemy in world
				if ((Ml_Enemy[i].x_coord + 16 >= -16 && Ml_Enemy[i].x_coord - 16 <= 16) && (Ml_Enemy[i].y_coord + 16 >= -16 && Ml_Enemy[i].y_coord - 16 <= 16)) {
					player->takeDamage(10); //Deal damage if it touches the player

					Ml_Enemy[i].AI("RETREAT");
				}
				else{
					Ml_Enemy[i].AI("IDLE");
				}
			}
		}

		int BG::testCollision(){
			collided();

			if (hit && m_window->isKeyPressed(GLFW_KEY_A) &&
				colCode == 0){
				colCode = 1;
			}
			else if (hit && m_window->isKeyPressed(GLFW_KEY_D) &&
				colCode == 0){
				colCode = 2;
			}
			else if (hit && m_window->isKeyPressed(GLFW_KEY_W) &&
				colCode == 0){
				colCode = 3;
			}
			else if (hit && m_window->isKeyPressed(GLFW_KEY_S) &&
				colCode == 0){
				colCode = 4;
			}
			else if (!hit){
				colCode = 0;
			}

			return colCode;
		}

		void BG::collided(){
			hit = false; //This bool is only for if the PLAYER hits something, everything else should
						 //only tell the respective AI to either stop or walk away

			// For player && Wall 
			//for (int i = 0; i < walls.size(); i++){
			//	if (walls[i].x_coord - (walls[i].m_width / 2) <= 16 && walls[i].x_coord + (walls[i].m_width / 2) >= -16
			//		&& walls[i].y_coord + (walls[i].m_height / 2) >= -16 && walls[i].y_coord - (walls[i].m_height / 2) <= 16){
			//		hit = true;
			//	}
			//}

			//// For player && Basic Enemy 
			//for (int i = 0; i < B_Enemy.size(); i++){
			//	if (B_Enemy[i].x_coord - (B_Enemy[i].m_width / 2) <= 16 && B_Enemy[i].x_coord + (B_Enemy[i].m_width / 2) >= -16
			//		&& B_Enemy[i].y_coord + (B_Enemy[i].m_height / 2) >= -16 && B_Enemy[i].y_coord - (B_Enemy[i].m_height / 2) <= 16){
			//		hit = true;
			//		B_Enemy[i].AI("REDIRECT");
			//	}
			//}

			//// For player && Melee Enemy 
			//for (int i = 0; i < Ml_Enemy.size(); i++){
			//	if (Ml_Enemy[i].x_coord - (Ml_Enemy[i].m_width / 2) <= 16 && Ml_Enemy[i].x_coord + (Ml_Enemy[i].m_width / 2) >= -16
			//		&& Ml_Enemy[i].y_coord + (Ml_Enemy[i].m_height / 2) >= -16 && Ml_Enemy[i].y_coord - (Ml_Enemy[i].m_height / 2) <= 16){
			//		hit = true;
			//		Ml_Enemy[i].AI("RETREAT");
			//	}
			//}

			//// For player && Basic Medic
			//for (int i = 0; i < B_Medics.size(); i++){
			//	if (B_Medics[i].x_coord - (B_Medics[i].m_width / 2) <= 16 && B_Medics[i].x_coord + (B_Medics[i].m_width / 2) >= -16
			//		&& B_Medics[i].y_coord + (B_Medics[i].m_height / 2) >= -16 && B_Medics[i].y_coord - (B_Medics[i].m_height / 2) <= 16){
			//		hit = true;
			//		B_Medics[i].AI("REDIRECT");
			//	}
			//}

			//// For Basic Enemy && Wall
			//for (int i = 0; i < walls.size(); i++){
			//	for (int e = 0; e < B_Enemy.size(); e++){
			//		if (walls[i].x_coord - (walls[i].m_width / 2) <= B_Enemy[e].x_coord + (B_Enemy[e].m_width / 2) && walls[i].x_coord + (walls[i].m_width / 2) >= B_Enemy[e].x_coord - (B_Enemy[e].m_width / 2)
			//			&& walls[i].y_coord + (walls[i].m_height / 2) >= B_Enemy[e].y_coord - (B_Enemy[e].m_height / 2) && walls[i].y_coord - (walls[i].m_height / 2) <= B_Enemy[e].y_coord - (B_Enemy[e].m_height / 2)){

			//			B_Enemy[e].AI("REDIRECT");
			//		}
			//	}
			//}
			//
			//// For Melee Enemy && Wall
			//for (int i = 0; i < walls.size(); i++){
			//	for (int e = 0; e < Ml_Enemy.size(); e++){
			//		if (walls[i].x_coord - (walls[i].m_width / 2) <= Ml_Enemy[e].x_coord + (Ml_Enemy[e].m_width / 2) && walls[i].x_coord + (walls[i].m_width / 2) >= Ml_Enemy[e].x_coord - (Ml_Enemy[e].m_width / 2)
			//			&& walls[i].y_coord + (walls[i].m_height / 2) >= Ml_Enemy[e].y_coord - (Ml_Enemy[e].m_height / 2) && walls[i].y_coord - (walls[i].m_height / 2) <= Ml_Enemy[e].y_coord - (Ml_Enemy[e].m_height / 2)){

			//			Ml_Enemy[e].AI("REDIRECT");
			//		}
			//	}
			//}

			//// For Base Medic && Wall
			//for (int i = 0; i < walls.size(); i++){
			//	for (int e = 0; e < B_Medics.size(); e++){
			//		if (walls[i].x_coord - (walls[i].m_width / 2) <= B_Medics[e].x_coord + (B_Medics[e].m_width / 2) && walls[i].x_coord + (walls[i].m_width / 2) >= B_Medics[e].x_coord - (B_Medics[e].m_width / 2)
			//			&& walls[i].y_coord + (walls[i].m_height / 2) >= B_Medics[e].y_coord - (B_Medics[e].m_height / 2) && walls[i].y_coord - (walls[i].m_height / 2) <= B_Medics[e].y_coord - (B_Medics[e].m_height / 2)){

			//			B_Medics[e].AI("REDIRECT");
			//		}
			//	}
			//}
		}

	}
}