#include "Door.h"

namespace spacey{ namespace environment{

	Door::Door(){
		x_coord = 0;
		y_coord = 0;
		width = 0;
		height = 0;
		stateFlag = "CLOSED";
		cDir = oDir = 0;
		m_width = 0;
		m_height = 0;
	}

	Door::~Door(){

	}

	Door::Door(int x, int y, int w,
		int h, int closed_dir, int open_dir, string filename){

		x_coord = x;
		y_coord = y;
		m_width = w;
		m_height = h;
		cDir = closed_dir;
		oDir = open_dir;
		dir = cDir;
		imageLoaded = loadImage(filename, m_image, u2, v2, u3, v3, width, height);
	}

	bool Door::checkRadius(Window* window){
		if (x_coord - (m_width + 20) <= 16 && x_coord + (m_width + 20) >= -16
			&& y_coord + (m_height + 20) >= -16 && y_coord - (m_height + 20) <= 16 && window->isKeyPressed(GLFW_KEY_SPACE)){
			cout << "Player input detected\n";
			return true;
		}

		return false;
	}

	void Door::update(bool radiusCheck){
		//Check if player is able to open the door
		if (counter >= waitTime && radiusCheck){
			counter = 0;

			//Update State flag
			if (stateFlag == "CLOSED"){
				stateFlag = changeState("OPEN");
			}
			else{
				stateFlag = changeState("CLOSED");
			}	
			
		}

		counter++;

	}

	string Door::changeState(string state){
		if (state == "OPEN"){
			
			rotate(oDir);

			cout << "Opened Door\n";
			return "OPEN";
		}

		else{
			
			rotate(cDir);

			cout << "Closed Door\n";
			return "CLOSED";
		}
	}

	void Door::rotate(int nState){

		/*switch (dir){
		case 1:
		if (m_height < 0)
		m_height = -m_height;
		break;
		case 3:
		if (m_width < 0)
		m_width = -m_width;
		break;
		case 5:
		if (m_height > 0)
		m_height = -m_height;
		break;
		case 7:
		if (m_width > 0)
		m_width = -m_width;
		break;
		default:
		cout << "Door is not in a valid direction\n";
		}*/

		if (nState < dir){
			motionObj.rotateLeft(90);
		}
		else{
			motionObj.rotateRight(90);
		}
	}
} }