#pragma once

#include "BaseObject.h"

namespace spacey{
	namespace objects{

		using namespace std;

		class Wall : public BaseObject{
		public:
			Wall();
			Wall(int width, int height, int x, int y, string type);			
		};
	}
}