#pragma once
#include "../graphics/Window.h"
#include "../motion/MotionController.h"
#include "../objects/BG.h"

namespace spacey{ namespace input{
	using namespace graphics;
	using namespace motion;
	using namespace background;

	void checkForInput(Window* window, Motion* motionObject, BG &background);

} }