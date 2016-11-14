#pragma once
#include <GL\glew.h>
#include <GL\GLU.h>
#include <cmath>
#include "../graphics/lodepng.h"
#include <string>
#include <iostream>

namespace spacey{
	namespace objects{

		using namespace std;

		bool loadImage(string filename, vector<unsigned char> &m_image, size_t &u2, size_t &v2, double &u3, 
			double &v3, unsigned &width, unsigned &height);
		
		bool loadAnimateable(string filename, vector<unsigned char> &m_image, size_t &u2, size_t &v2, unsigned &width, unsigned &height);

		struct BaseObject{
			void Draw();
			float x_coord = 0;
			float y_coord = 0;

			//Image Variables
			vector<unsigned char> m_image;
			unsigned width, height;
			size_t u2 = 1;
			size_t v2 = 1;
			double u3;
			double v3;
			bool imageLoaded = false;

			//Size Variables
			int iWidth, iHeight;
		};
	}
}