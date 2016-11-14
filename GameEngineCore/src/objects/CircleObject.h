#pragma once
#include <GL\glew.h>
#include <GL\GLU.h>
#include <cmath>
#include <math.h>
#include "BaseObject.h"

namespace spacey{ namespace objects{
		
	class CircleObject : public BaseObject{
		public:
			CircleObject();
			CircleObject(float x_in, float y_in, float radius_in, string filename);
			void Draw();
			float radius;
		};
} }