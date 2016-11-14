#pragma once
#include "BaseEntity.h"
#include "Bullet.h"
#include "PlayerObject.h"
#include "../motion/MotionController.h"
#include <GL\glew.h>
#include <GL\GLU.h>
#include <vector>
#include <stdlib.h>

namespace spacey{ namespace objects{

	using namespace motion;

	class BaseEnemy : public Bullet, public BaseEntity{	
	public:
		BaseEnemy(); //Constructor
		~BaseEnemy(); //Destructor

		BaseEnemy(int x, int y, int tWidth, int tHeight, string filename); //Overload Function

		std::vector<Bullet> delaware; 
		
		const int STEP_MAX = 300;
		int steps;

	private:
		int counter;
		int direction = 3;
		int pointing = 0;
		
		void createNewBullet(); //Creates new bullet every x ticks
		void bulletFill(); //Fills bullet vector
		void walk(); //Enemy moves

		void pursue(); //Follows player until they are either dead or own health is too low
		void flee(); //Runs away form the player

		float p_x;
		float p_y;
		int p_health;
	public:
		void AI(string indicator);
		bool checkArea(PlayerObject player);

	public:
		BaseEnemy operator=(BaseEnemy right);
	};

} }