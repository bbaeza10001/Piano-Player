#include "Orbits.h"

namespace spacey{ namespace motion{
	
	Orbit::Orbit(){
		counter.clear();
		xDistance.clear();
		yDistance.clear();
	}

	void Orbit::orbit(vector<CircleObject> &starSystem){
		for (float i = 0.0f; i < starSystem.size(); i++){
			xDistance.push_back((abs(starSystem[0].x_coord - starSystem[i].x_coord)));
			yDistance.push_back((abs(starSystem[0].y_coord - starSystem[i].y_coord)));
			angle.push_back((atan(yDistance[i] / xDistance[i])) * 0.01);
			counter.push_back(0.0f);
		}

		for (float i = 1.0f; i < starSystem.size(); i++){
			counter[i] += angle[i]; //Angle that the object moves by 

			//Horizontal
			starSystem[i].x_coord = (xDistance[i] * (std::cos(counter[i] * full_angle / 360.0f))) + starSystem[0].x_coord;

			//Vertical
			starSystem[i].y_coord = (yDistance[i] * (std::sin(counter[i] * full_angle / 360.0f))) + starSystem[0].y_coord;

			glTranslatef(starSystem[i].x_coord, starSystem[i].y_coord, 0);

			if (counter[i] > 360.0f){
				counter[i] = 0.0f;
			}
		}
		
	}

} }