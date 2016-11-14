#pragma once

#include "BaseObject.h"
#include <iostream>

namespace spacey{ namespace objects{

	class Bullet {
	public:
		Bullet();
		Bullet(int direction, float x, float y);
		void Fire();

		bool limit();

		float bX;
		float bY;

		Bullet operator=(Bullet right);
	private: //Functions
		void Move();

	private: //Variables
		int m_direction;

		float bx_coord;
		float by_coord;

		const int LIMIT = 400;
		const float MOVE_RATE = 1.0f;

		//Image Variables
		vector<unsigned char> m_bimage;
		unsigned b_width, b_height;
		size_t b_u2 = 1;
		size_t b_v2 = 1;
		double b_u3;
		double b_v3;
		bool b_imageLoaded = false;
	};

} }