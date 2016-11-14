#include "Wall.h"

namespace spacey{
	namespace objects{

		Wall::Wall(){
			x_coord = 0;
			y_coord = 0;
		}

		Wall::Wall(int width, int height, int x, int y, string type){
			iWidth = width;
			iHeight = height;
			x_coord = x;
			y_coord = y;

			string filename;

			if (type == "TEST"){
				filename = "Resources/Images/Basic_Wall.png";
			}
			else if (type == "BRICK"){

			}
			else if (type == "STONE"){

			}

			unsigned temp, temp2;

			imageLoaded = loadImage(filename, m_image, u2, v2, u3, v3, temp, temp2);
		}
	}
}