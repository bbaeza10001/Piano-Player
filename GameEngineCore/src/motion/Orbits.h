#pragma once
#include "../objects/CircleObject.h"
#include <vector>
#include <cmath>
#include <iostream>

namespace spacey{ namespace motion{

	using namespace std;
	using namespace objects;

	class Orbit{
	public:
		Orbit();
		void orbit(vector<CircleObject> &starSystem);

	private:
		const float full_angle = 2.0f*3.141592654f;
		vector<float> counter;
		vector<float> xDistance;
		vector<float> yDistance;
		vector<float> angle;
	};

} }