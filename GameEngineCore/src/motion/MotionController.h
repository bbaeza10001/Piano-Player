#pragma once
#include <GL\glew.h>
#include <GL\GLU.h>
#include <cmath>
#include <iostream>

namespace spacey{ namespace motion{

	using namespace std;

	class Motion{
	public:
		void dirRight();
		void dirLeft();
		void dirUp();
		void dirDown();

		void rotateLeft(int angle);
		void rotateRight(int angle);

		void applySpeed();
		void applyRotation(float x, float y);
		
		//For Translations
		float xspeed = 0;
		float yspeed = 0;
		
		//For Rotations
		float angle = 0;

		//For Animations
		string animFlag;
	private:
		//Incriments
		const float speed = 1.0f; //Number of pixel spaces moved per cycle
		const float angleIncriment = 22.5f;

	};

} }