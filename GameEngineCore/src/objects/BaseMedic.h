//Written by Will and Kenny
#pragma once
#include "BaseEntity.h"
#include "BaseEnemy.h"
#include "MeleeEnemy.h"
#include "../motion/MotionController.h"
#include <GL\glew.h>
#include <GL\GLU.h>
#include <vector>
#include <stdlib.h>

namespace spacey{
	namespace objects{

		using namespace motion;

		class BaseMedic : public BaseEntity{
		public:
			BaseMedic(); //Constructor
			~BaseMedic(); //Destructor

			BaseMedic(int x, int y, int tWidth, int tHeight, string filename); //Overload Function
			
		private: //Orientation
			int counter;
			int direction = 3;
			int pointing = 0;

		private: //Healing and AI 
			void move();
			
			int steps = 0;
			const int STEP_MAX = 500;

		public:
			void AI(string indicator);

			void Heal(BaseEntity* entity, unsigned int i, string type);

			unsigned int healing;
			string healType;
			bool available = true;

		private: //Operator Overloads
			BaseMedic operator=(BaseMedic right);
		};
	}
}