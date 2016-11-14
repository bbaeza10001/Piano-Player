#include "Inventory.h"

namespace spacey{
	namespace GUI{
		Inventory::Inventory(){
			std::fill_n(taken, 9, false);
			
		}

		void Inventory::Init(Window* window, string filename){
			m_window = window;

			iWidth = window->getWidth();
			iHeight = window->getHeight();

			imageLoaded = loadImage(filename, m_image, u2, v2, u3, v3, width, height);
		}

		void Inventory::update(){
			if (open){
				if (!drawing){
					//render = std::thread(&Inventory::rend, this);
					////render.detach();
					//drawing = true; 
					//std::cout << "Inventory drawing on separate thread\n";
					rend();
				}
			}
			else{
				//std::cout << "Inventory closed\n";
			}
		}

		void Inventory::rend(){
			std::cout << "Begin Inven Drawing\n";

			if (imageLoaded){
				// Enable the texture for OpenGL.
				glEnable(GL_TEXTURE_2D);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//GL_LINEAR = smoothing
				glTexImage2D(GL_TEXTURE_2D, 0, 4, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &m_image[0]);

				/*u3 = iWidth / u2;
				v3 = iHeight / v2;*/

				//Draw the texture
				glPushMatrix();

				glBegin(GL_QUADS);
				glTexCoord2d(0, v3);	 glVertex2d(x_coord - (iWidth / 2), y_coord - (iHeight / 2));
				glTexCoord2d(0, 0);		 glVertex2d(x_coord - (iWidth / 2), y_coord + (iHeight / 2));
				glTexCoord2d(u3, 0);	 glVertex2d(x_coord + (iWidth / 2), y_coord + (iHeight / 2));
				glTexCoord2d(u3, v3);	 glVertex2d(x_coord + (iWidth / 2), y_coord - (iHeight / 2));
				glEnd();

				glPopMatrix();
			}
		}

		void Inventory::addtoInventory(BaseItem item){
			for (int i = 0; i < 9; i++){

				if (!taken[i]){
					container[i] = item;
					taken[i] = true;
				}
				else if (i == 8 && taken[i]){
					cout << "No more space in your inventory!\n";
				}

			}
		}

		/*void Inventory::select(int index){

		}

		void Inventory::drop(int index){

		}

		void Inventory::drawItems(){

		}*/
	}
}