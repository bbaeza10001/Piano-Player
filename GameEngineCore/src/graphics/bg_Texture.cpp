#include "bg_Texture.h"

namespace spacey{
	namespace graphics{
		bg_Texture::bg_Texture(){
			m_image.empty();
			width = 0;
			height = 0;
			imageLoaded = false;
		}

		bg_Texture::bg_Texture(Window* window, string filename, int x, int y, int width, int height, bool parallax){
			x_coord = x;
			y_coord = y;
			m_window = window;
			imageLoaded = loadBG(filename); //Filling parameters

			if (imageLoaded)
				cout << "Loaded background image.\n";

			repeatAmtY = height / this->height;
			repeatAmtX = width / this->width;

			this->width = width;
			this->height = height;

			paral = parallax;
		}

		void bg_Texture::Draw(){
			if (imageLoaded){
				// Enable the texture for OpenGL.
				glEnable(GL_TEXTURE_2D);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//Setting image to repeat on background
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_NEAREST = no smoothing
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //GL_LINEAR = smoothing
				glTexImage2D(GL_TEXTURE_2D, 0, 4, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &m_image[0]);

				if (paral)
					parallax();

				//Drawing the image
				glPushMatrix();

				glBegin(GL_QUADS);
				glTexCoord2d(0, 0);						glVertex2d(x_coord, y_coord);
				glTexCoord2d(0, repeatAmtY);			glVertex2d(x_coord, y_coord + height);
				glTexCoord2d(repeatAmtX, repeatAmtY);   glVertex2d(x_coord + width, y_coord + height);
				glTexCoord2d(repeatAmtX, 0);			glVertex2d(x_coord + width, y_coord);
				glEnd();

				glPopMatrix();


			}
		}

		void bg_Texture::parallax(){
			if (m_window->isKeyPressed(GLFW_KEY_A))
				x_coord++;
			if (m_window->isKeyPressed(GLFW_KEY_D))
				x_coord--;
			if (m_window->isKeyPressed(GLFW_KEY_W))
				y_coord--;
			if (m_window->isKeyPressed(GLFW_KEY_S))
				y_coord++;
		}

		bool bg_Texture::loadBG(string filename){
			
			// Load file and decode image.
			vector<unsigned char> image;
			unsigned error = lodepng::decode(image, width, height, filename);
			
			// If there's an error, display it.
			if (error != 0)
			{
				std::cout << "error " << error << ": " << lodepng_error_text(error) << std::endl;
				return false;
			}

			// Make some OpenGL properties better for 2D and enable alpha channel.
			glDisable(GL_CULL_FACE);
			glDisable(GL_DEPTH_TEST);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glDisable(GL_ALPHA_TEST);


			if ((width % 2) != 0 || (height % 2) != 0){

				// Texture size must be power of two for the primitive OpenGL version this is written for. Find next power of two.
				u2 = 1;  while (u2 < width) u2 *= 2;
				v2 = 1;  while (v2 < height) v2 *= 2;
				// Ratio for power of two version compared to actual version, to render the non power of two image with proper size.
				u3 = (double)width / u2;
				v3 = (double)height / v2;

				// Make power of two version of the image.
				std::vector<unsigned char> image2(u2 * v2 * 4);
				for (size_t y = 0; y < height; y++)
					for (size_t x = 0; x < width; x++)
						for (size_t c = 0; c < 4; c++)
						{
							image2[4 * u2 * y + 4 * x + c] = image[4 * width * y + 4 * x + c];
						}

				m_image = image2;
			}
			else{
				u3 = u2 = width;
				v3 = v2 = height;
				m_image = image;
			}


			return true;
		}
	}
}