#pragma once
#include <GL\glew.h>
#include <GL\GLU.h>
#include <cmath>
#include "../graphics/lodepng.h"
#include "../motion/MotionController.h"
#include <string>
#include <iostream>

namespace spacey{
	namespace objects{
		using namespace motion;
		using namespace std;

		class BaseEntity{

		public:
			void Draw();
			float x_coord = 0;
			float y_coord = 0;

		public: //Information
			int health = 50;
			int m_width = 32;
			int m_height = 32;

		protected: //Image Variables
			vector<unsigned char> m_image;
			unsigned width, height;
			size_t u2 = 1;
			size_t v2 = 1;
			double u3;
			double v3;
			bool imageLoaded = false;

		private: //Animation
			void checkAnimState();
			void animate(int frameSpeed, int startFrame, int maxFrames);
		
		protected: 
			Motion mObj;
			int counter = 0;
			int currentFrame = 0;
			int framesPerRow;
			int m_texWidth;
			int m_texHeight;

		public: //AI
			virtual void AI(string indicator) = 0;

		protected:
			string AI_Flag;
		};
	}
}