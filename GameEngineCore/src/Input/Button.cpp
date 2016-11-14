#include "Button.h"

namespace spacey{ namespace input{

	button::button(){
		m_width = 0;
		m_height = 0;
		m_x = 0;
		m_y = 0;
		m_window = NULL;
	}

	button::button(Window* window, double x, double y, double in_width, double in_height, string filename){
		m_x = x;
		m_y = y;
		m_window = window;
		m_filename = filename;
		m_width = in_width;
		m_height = in_height;

		// Load file and decode image.
		std::vector<unsigned char> image;
		unsigned width, height;
		// Here the PNG is loaded in "image"
		lodepng::decode(image, width, height, filename);


		// Make some OpenGL properties better for 2D and enable alpha channel.
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glDisable(GL_ALPHA_TEST);

		// Texture size must be power of two for the primitive OpenGL version this is written for. Find next power of two.
		while (u2 < width) u2 *= 2;
		while (v2 < height) v2 *= 2;
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

	void button::draw(){
		// Enable the texture for OpenGL.
		glEnable(GL_TEXTURE_2D);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &m_image[0]);

		//Draw the image on a polygon
		glPushMatrix();

		glBegin(GL_QUADS);
		glTexCoord2d(0, 0);    glVertex2d(m_x - (m_width / 2), m_y - (m_height / 2));
		glTexCoord2d(0, v3);   glVertex2d(m_x - (m_width / 2), m_y + (m_height / 2));
		glTexCoord2d(u3, v3);  glVertex2d(m_x + (m_width / 2), m_y + (m_height / 2));
		glTexCoord2d(u3, 0);   glVertex2d(m_x + (m_width / 2), m_y - (m_height / 2));
		glEnd();

		glPopMatrix();
	}

	bool button::clicked(){
		if (m_window->isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)){
			double x, y;
			m_window->getMousePosition(x, y);

			if (m_x - (m_width / 2) <= x && m_x + (m_width / 2) >= x
				&& m_y + (m_height / 2) >= y && m_y - (m_height / 2) <= y){

				return true;
			}

			return false;
		}

		return false;
	}
} }