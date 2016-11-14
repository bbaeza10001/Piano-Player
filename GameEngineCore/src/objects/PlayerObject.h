#pragma once

#include <GL\glew.h>
#include <cmath>
#include <ctime>
#include <vector>
#include <GL/glu.h>
#include <GL/gl.h>
#include "Bullet.h"
#include "../graphics/Window.h"
#include "../motion/MotionController.h"
#include "BaseEntity.h"
#include "Inventory.h"

namespace spacey{
	namespace objects{
		using namespace std;
		using namespace graphics;
		using namespace motion;
		using namespace GUI;

		class PlayerObject : public Bullet, public BaseEntity{
		public:
			PlayerObject(Window* window, Motion* motion, string filename, int texWidth, int texHeight);

			int health = 100;
			vector<Bullet> shot;
			void takeDamage(int amount);

		public:
			void AI(string indicator);
			void checkRotation(Motion* motion);
			void checkFire();
			void regenHealth();

		private: //Misc
			Window* m_window;
			Motion* motionObj;
			int direction = 3;

		private: //Clock varaibles
			clock_t start;
			double passed;
			const double wait = 0.5;

			clock_t delay; //Clock for how fast you can shoot
			double waited;
			const double shotLast = 2;

			clock_t healthStart;
			double healthPassed;
			const double healthWait = 30.0;

		public: //Inventory
			Inventory inven;

		private: 
			int tick;
			const int MINIMUM_INVEN_TICK = 10;
			bool openInven();

		};
	}
}