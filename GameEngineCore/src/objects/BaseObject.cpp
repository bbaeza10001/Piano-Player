#include "BaseObject.h"

namespace spacey{
	namespace objects{

		bool loadImage(string filename, vector<unsigned char> &m_image, size_t &u2, size_t &v2, double &u3,
			double &v3, unsigned &width, unsigned &height){

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
			glEnable(GL_ALPHA);

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

			return true;
		}

		bool loadAnimateable(string filename, vector<unsigned char> &m_image, size_t &u2, size_t &v2, 
			unsigned &width, unsigned &height){

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

			// Texture size must be power of two for the primitive OpenGL version this is written for. Find next power of two.
			u2 = 1;  while (u2 < width) u2 *= 2;
			v2 = 1;  while (v2 < height) v2 *= 2;

			// Make power of two version of the image.
			std::vector<unsigned char> image2(u2 * v2 * 4);
			for (size_t y = 0; y < height; y++)
				for (size_t x = 0; x < width; x++)
					for (size_t c = 0; c < 4; c++)
					{
						image2[4 * u2 * y + 4 * x + c] = image[4 * width * y + 4 * x + c];
					}

			m_image = image2;

			return true;
		}

		void BaseObject::Draw(){

			if (imageLoaded){
				// Enable the texture for OpenGL.
				glEnable(GL_TEXTURE_2D);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//GL_LINEAR = smoothing
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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
			glPopMatrix();
		}
	}
}