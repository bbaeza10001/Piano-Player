#include "BaseItem.h"

namespace spacey{
	namespace items{

		BaseItem::BaseItem(){
			x_coord = 0;
			y_coord = 0;
			m_image.clear();
			width = 0;
			height = 0;
			u3 = 0;
			v3 = 0;
			type = 0;
		}

		BaseItem::~BaseItem(){

		}

		BaseItem::BaseItem(int x, int y, string filename){
			x_coord = x;
			y_coord = y;

			imageLoaded = loadImage(filename, m_image, u2, v2, u3, v3, width, height);
		}

		void BaseItem::draw(Motion* motion){
			x_coord += motion->xspeed;
			y_coord += motion->yspeed;

			if (imageLoaded){
				// Enable the texture for OpenGL.
				glEnable(GL_TEXTURE_2D);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_NEAREST = no smoothing
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexImage2D(GL_TEXTURE_2D, 0, 4, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &m_image[0]);

				//Draw the image on a polygon
				glPushMatrix();

				glBegin(GL_QUADS);
				glTexCoord2d(0, v3);	glVertex2d(x_coord - (m_width / 2), y_coord - (m_height / 2));
				glTexCoord2d(0, 0);		glVertex2d(x_coord - (m_width / 2), y_coord + (m_height / 2));
				glTexCoord2d(u3, 0);	glVertex2d(x_coord + (m_width / 2), y_coord + (m_height / 2));
				glTexCoord2d(u3, v3);	glVertex2d(x_coord + (m_width / 2), y_coord - (m_height / 2));
				glEnd();

				glPopMatrix();

			}
			else {
				cout << "Could not load image(s)\n";
			}
		}

		bool BaseItem::isPickedUp(BaseEntity* entity){
			
			if (entity->x_coord - (entity->m_width / 2) <= x_coord + (m_width / 2) && entity->x_coord + (entity->m_width / 2) >= x_coord - (m_width / 2)
				&& entity->y_coord + (entity->m_height / 2) >= y_coord - (m_height / 2) && entity->y_coord - (entity->m_height / 2) <= y_coord + (m_height / 2)){
				
				return true;
			}

			return false;
		}
	}
}