#pragma once

#include <GL\glew.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include "BaseObject.h"
#include "../Items/BaseItem.h"
#include "../graphics/Window.h"
#include <thread>

namespace spacey{
	namespace GUI{
		using namespace objects;
		using namespace graphics;
		using namespace items;

		class Inventory : public BaseObject{
		public:

			Inventory();
			void addtoInventory(BaseItem item);
			bool open = false;
			void rend();

		public: // Loader functions to work around a construction error in the Player.H 

			void Init(Window* window, string filename);
			void update();

		protected: // Navigation functions

			/*void select(int index);
			void drop(int index);
			void drawItems();*/

		private: // Necessary variables

			Window* m_window;
			bool IsOpened = false;
			BaseItem container[9];
			bool taken[9];
			bool drawing = false;

		public:
			std::thread render;

		};
	}
}