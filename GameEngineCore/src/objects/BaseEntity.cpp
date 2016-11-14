#include "BaseEntity.h"

namespace spacey{
	namespace objects{

		void BaseEntity::checkAnimState(){

			if (mObj.animFlag == "IDLE"){
				currentFrame = 0;
			}
			else if (mObj.animFlag == "WALK_RIGHT"){
				animate(30, 27, 35);
			}
			else if (mObj.animFlag == "WALK_LEFT"){
				animate(30, 9, 17);
			}
			else if (mObj.animFlag == "WALK_DOWN"){
				animate(30, 18, 26);
			}
			else if (mObj.animFlag == "WALK_UP"){
				animate(50, 0, 9);
			}
		}

		void BaseEntity::animate(int frameSpeed, int startFrame, int maxFrames){
			if (counter == (frameSpeed - 1)){
				currentFrame = (currentFrame + 1) % maxFrames;

				while (currentFrame < startFrame)
					currentFrame++;

			}

			counter = (counter + 1) % frameSpeed;

		}

		void BaseEntity::Draw(){
			checkAnimState();
			AI(AI_Flag);

			if (imageLoaded){
				// Enable the texture for OpenGL.
				glEnable(GL_TEXTURE_2D);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_NEAREST = no smoothing
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexImage2D(GL_TEXTURE_2D, 0, 4, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &m_image[0]);

				//Converting the texture sizes from a pixel scale to an image scale
				/*NOTE: It is important to divide the textures pixel size by the converted images full width
				and height (u2 and v2 respectively), otherwise, the texture will be overdrawn due to scaling
				issues form the conversion*/
				double tWidth = m_texWidth / (double)u2;
				double tHeight = m_texHeight / (double)v2;

				/*Finding the current x and y coordinates in the texture based on what the current frame is.
				Note: The tX math will automatically move down a row if it is at the end of the row.*/
				double tX = (currentFrame % framesPerRow) * (double)tWidth;
				double tY = (currentFrame / framesPerRow) * (double)tHeight;

				//Draw the image on a polygon
				glPushMatrix();
				
				glBegin(GL_QUADS);
				glTexCoord2d(tX, tY + tHeight);				glVertex2d(x_coord - 32, y_coord - 32);
				glTexCoord2d(tX, tY);						glVertex2d(x_coord - 32, y_coord + 32);
				glTexCoord2d(tX + tWidth, tY);				glVertex2d(x_coord + 32, y_coord + 32);
				glTexCoord2d(tX + tWidth, tY + tHeight);	glVertex2d(x_coord + 32, y_coord - 32);
				glEnd();

				glPopMatrix();
				

			}
			else {
				cout << "Failed to load image(s)\n";
			}

		}
	}
}