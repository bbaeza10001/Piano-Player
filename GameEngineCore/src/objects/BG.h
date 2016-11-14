#pragma once

#include <iostream>
#include <vector>
#include "BaseEnemy.h"
#include "PlayerObject.h"
#include "MeleeEnemy.h"
#include "Wall.h"
#include "Door.h"
#include "BaseMedic.h"
#include "../graphics/Window.h"
#include "../graphics/LoadLevel.h"
#include "../motion/Orbits.h"
#include "../motion/MotionController.h"

namespace spacey{
	namespace background{

		using namespace std;
		using namespace objects;
		using namespace level;
		using namespace motion;
		using namespace graphics;
		using namespace environment;

		class BG{
		public: //Set up functions
			BG();
			BG(Window* window);
			void loadFile(string filename, string type);

			void update(Motion* motion, PlayerObject* player);

		public: //Other Functions
			int testCollision();

		private: //Personal Functions
			void collided();
			void move(Motion* motion, PlayerObject* player);
			void checkBullets(PlayerObject* player);

		private: //Objects
			vector<BaseEnemy> B_Enemy;
			vector<Wall> walls;
			vector<MeleeEnemy> Ml_Enemy;
			vector<Door> doors;
			vector<BaseMedic> B_Medics;

			vector<BaseObject> environment;
			vector<BaseEntity*> entities;

		private: //Tools
			Window* m_window;
			Orbit orb;
			bool hit = false;
			int colCode;
		};
	}
}