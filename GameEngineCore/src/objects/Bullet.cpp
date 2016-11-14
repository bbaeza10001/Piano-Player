#include "Bullet.h"

namespace spacey{ 	namespace objects{

	Bullet::Bullet(){
		m_direction = 0;
	}

	Bullet::Bullet(int direction, float x, float y){
		m_direction = direction;
		bx_coord = bX = x;
		by_coord = bY = y;
		b_imageLoaded = loadImage("Resources/Images/Base_Bullet.png", m_bimage, b_u2, b_v2, b_u3, b_v3, b_width, b_height);
	}

	void Bullet::Fire(){

		if (b_imageLoaded){
			// Enable the texture for OpenGL.
			glEnable(GL_TEXTURE_2D);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, b_u2, b_v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &m_bimage[0]);

			//Draw the image on a polygon
			glPushMatrix();
			Move();
			glBegin(GL_QUADS);
			glTexCoord2d(0, b_v3);	glVertex2d(bX - 8, bY - 16);
			glTexCoord2d(0, 0);		glVertex2d(bX - 8, bY + 16);
			glTexCoord2d(b_u3, 0);	glVertex2d(bX + 8, bY + 16);
			glTexCoord2d(b_u3, b_v3);	glVertex2d(bX + 8, bY - 16);
			glEnd();
			
			glPopMatrix();

		}
		else{

			glPushMatrix();
			Move();
			glColor3f(1, 1, 0.5);
			glBegin(GL_QUADS);
			glVertex2f(bX - 1, bY);
			glVertex2f(bX + 1, bY);
			glVertex2f(bX + 1, bY - 2);
			glVertex2f(bX - 1, bY - 2);
			glEnd();
			
			glPopMatrix();
		}
		
	}

	bool Bullet::limit(){

		if ((bX - LIMIT) > bx_coord || (bX + LIMIT) < bx_coord){
			return true;
		}

		else if ((bY - LIMIT) > by_coord || (bY + LIMIT) < by_coord){
			return true;
		}
		else{
			return false;
		}
	}

	void Bullet::Move(){
		switch (m_direction){
		case 1: //Move Up
			bY += MOVE_RATE;
			break;
		case 2: //Move Up Right
			bX += MOVE_RATE;
			bY += MOVE_RATE;
			break;
		case 3: //Move Right
			bX += MOVE_RATE;
			break;
		case 4: //Move Down Right
			bX += MOVE_RATE;
			bY -= MOVE_RATE;
			break;
		case 5: //Move Down
			bY -= MOVE_RATE;
			break;
		case 6: //Move Down Left
			bX -= MOVE_RATE;
			bY -= MOVE_RATE;
			break;
		case 7: //Move Left
			bX -= MOVE_RATE;
			break;
		case 8: //Move Up Left
			bX -= MOVE_RATE;
			bY += MOVE_RATE;
			break;
		default: //Print out an error message
			std::cout << "Error: Bullet orientation is invalid.\n";
			std::cout << "Direction Code is: " << m_direction << std::endl;
			break;
		}
		
	}

	Bullet Bullet::operator=(Bullet right){

		Bullet temp;
		temp.bX = right.bX;
		temp.bx_coord = right.bx_coord;
		temp.bY = right.bY;
		temp.by_coord = right.by_coord;
		temp.b_height = right.b_height;
		temp.b_imageLoaded = right.b_imageLoaded;
		temp.b_u2 = right.b_u2;
		temp.b_u3 = right.b_u3;
		temp.b_v2 = right.b_v2;
		temp.b_v3 = right.b_v3;
		temp.b_width = right.b_width;
		temp.m_bimage = right.m_bimage;
		temp.m_direction = right.m_direction;
		
		return temp;
	}
} }