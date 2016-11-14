#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include "../objects/CircleObject.h"
#include "../objects/BaseEnemy.h"
#include "../objects/Wall.h"
#include "../objects/MeleeEnemy.h"
#include "../objects/Door.h"
#include "../objects/BaseMedic.h"

namespace spacey{ namespace level{

	using namespace objects;
	using namespace environment;
	using namespace std;

	void loadObject(vector<BaseObject> &container, string fileName);
	void loadEntity(vector<BaseEntity*> &container, string fileName);


	static string pathImage = "Resources/Images/";
	static string pathLevel = "Resources/Levels/";
	static string pathAudio = "Resources/Audio/";

} }