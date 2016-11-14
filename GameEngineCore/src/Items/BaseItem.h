#pragma once
#include <string>
#include <vector>
#include "../objects/BaseObject.h"
#include "../motion/MotionController.h"
#include "../objects/BaseEntity.h"

namespace spacey{
	namespace items{

		using namespace std;
		using namespace objects;
		using namespace motion;

		class BaseItem{
			
		public:
			BaseItem();
			~BaseItem();

			BaseItem(int x, int y, string filename);

			void draw(Motion* motion);
			bool isPickedUp(BaseEntity* entity);

		public: 
			float x_coord;
			float y_coord;
			float m_width = 16;
			float m_height = 16;
			int type;

		protected: //Image Necessities
			vector<unsigned char> m_image;
			unsigned width, height;
			size_t u2 = 1;
			size_t v2 = 1;
			double u3;
			double v3;
			bool imageLoaded = false;
		};
	}
}