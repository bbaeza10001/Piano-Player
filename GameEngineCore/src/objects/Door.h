#pragma once

#include "BaseObject.h"
#include "../graphics/Window.h"
#include "../motion/MotionController.h"
#include "PlayerObject.h"

namespace spacey { namespace environment {

	using namespace objects;
	using namespace graphics;
	using namespace motion;
	using namespace std;

	class Door : public BaseObject {

	public:
		Door();
		~Door();

		Door(int x, int y, int width, 
			int height, int closed_dir, int open_dir, string filename);

	private: //Associated objects/variables
		string stateFlag = "CLOSED";
		int cDir;
		int oDir;
		int dir;
		int m_width;
		int m_height;

		Motion motionObj;

	private: //Timer Variables
		int counter = 0;
		int waitTime = 20;

	private: //Member Functions
		bool checkRadius(Window* window);
		void update(bool radiusCheck);
		string changeState(string state);

	private: //Rotation Functions
		void rotate(int newState);
	};

} }