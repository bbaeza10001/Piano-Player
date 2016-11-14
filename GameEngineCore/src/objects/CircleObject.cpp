#include "CircleObject.h"

namespace spacey{
	namespace objects{
		CircleObject::CircleObject(){
			radius = 1;
			x_coord = 0;
			y_coord = 0;
		}

		CircleObject::CircleObject(float x_in, float y_in, float radius_in, string filename){
			x_coord = x_in;
			y_coord = y_in;
			radius = radius_in;
			imageLoaded = loadImage(filename, m_image, u2, v2, u3, v3, width, height);
		}

		void CircleObject::Draw(){
			if (imageLoaded){
				//Draw circle w/ a texture
				// Enable the texture for OpenGL.
				glEnable(GL_TEXTURE_2D);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_NEAREST = no smoothing
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//GL_LINEAR = smoothing
				glTexImage2D(GL_TEXTURE_2D, 0, 4, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &m_image[0]);

				//Draw the texture
				glPushMatrix();

				glTranslatef(x_coord, y_coord, 0);
				glBegin(GL_QUADS);
				glTexCoord2d(0, v3);		 glVertex2d(x_coord - radius, y_coord - radius);
				glTexCoord2d(0, 0);		 glVertex2d(x_coord - radius, y_coord + radius);
				glTexCoord2d(u3, 0);	 glVertex2d(x_coord + radius, y_coord + radius);
				glTexCoord2d(u3, v3);		 glVertex2d(x_coord + radius, y_coord - radius);
				glEnd();

				glPopMatrix();
			}
			else{
				//Draw circle w/o a texture
				const float full_angle = 2.0f*3.141592654f;
				float xN = 0.0f;
				float yN = 0.0f;

				glPushMatrix();
				glTranslatef(x_coord, y_coord, 0);
				glBegin(GL_POLYGON);
				for (float i = 0; i < 180; i++)
				{
					xN = radius * (std::cos(i * full_angle / 180.0f));
					yN = radius * (std::sin(i * full_angle / 180.0f));


					glColor3f((xN * 0.01), (yN * 0.01), 0.5f); //Sets color of planets
					glVertex2d(xN, yN);
				}
				glEnd();

				glPopMatrix();

			}

		}
	}
}