#include "src\include\Includes.h"
#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>
#include "src\graphics\bg_Texture.h"

#include "src\objects\Inventory.h"

#include <stdlib.h>

#include <thread>

using namespace spacey;
using namespace graphics;
using namespace objects;
using namespace std;
using namespace level;
using namespace input;
using namespace motion;

using namespace GUI;

/*
NOTES:

-Give the door class its own draw function
-Figure out which parts of code can be done in parallel

*/

#if 0
int main(){
	//Width and height for the game window
	int width = 960;
	int height = 720;

	//Start Screen
	static Window start("Arorbis - Start", width, height);

	//OpenGl Coordinate Grid Setup
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, height, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	bg_Texture background(&start, "Resources/Images/start_screen.png", 0, 0, 960, 720, false);

	button b_start(&start, 900, 135, 220, 120, "Resources/Images/empty_button.png");
	button b_exit(&start, (width / 2) + 20, (height / 2) + 60, 50, 40, "Resources/Images/empty_button.png");
	bool exit = true;

	while (!start.closed()){
		start.clear();

		background.Draw();

		b_start.draw();
		b_exit.draw();

		if (b_start.clicked()){
			start.~Window();
			exit = false;
		}
		else if (b_exit.clicked()){
			start.~Window();
		}

		start.update();

		double x, y;
		start.getMousePosition(x, y);
		cout << x << ", " << y << endl;
	}
	//bullshit from George's anus
	
	if (exit == false){

		glViewport(0, 0, width, height);

		//Changing the in-game window's width and height to something more eye catching
		width = 960;
		height = 720;

		//Game Window
		static Window window("Arorbis - DEMO", width, height);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //Game background color

		//OpenGL Coordinate Grid Setup
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-width / 2.0, width / 2.0, -height / 2.0, height / 2.0); //Sets coordinate system to start in 					
		glMatrixMode(GL_MODELVIEW);											//the middle of the screen like a standard graph
		glLoadIdentity();
		
		bg_Texture floor(&window, "Resources/Images/FloorTile1.png", -800, -600, 1600, 1200, true);

		// Construction
		Motion motion;
		PlayerObject player(&window, &motion, "Resources/Images/Multi-Layer.png", 37, 37);
		BG test(&window);
		test.loadFile("Resources/Levels/Wall.txt", "ENVIRONMENT");
		//test.loadFile("Resources/Levels/Doors.txt", "ENVIRONMENT");
		/*test.loadFile("Resources/Levels/Medics.txt", "ENTITY");
		test.loadFile("Resources/Levels/Enemy.txt", "ENTITY");
		test.loadFile("Resources/Levels/MeleeEnemy.txt", "ENTITY");*/
				
		while (!window.closed()){
			window.clear();

			checkForInput(&window, &motion, test); //Getting input values from the player in the current window


			floor.Draw();
			test.update(&motion, &player);
			player.Draw();

			window.update();
			Sleep(0.5); //Controls how fast the game loop runs at max
		}

	}
	return 0;
}
#endif

/*This alternate main function can be activated to test specific items that 
would otherwise be too messy to test in the main game version. To activate this 
instead of the game's main function, change the 0 after #if to 1, then change the #if 1 
above the original main function to #if 0 (This part is above this current text, almost at the top of the page)*/
#if 0
int main(){
	int width = 1920;
	int height = 1080;

	//Game Window
	static Window window("Still Alive", width, height);

	//OpenGL Coordinate Grid Setup
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-width / 2.0, width / 2.0, -height / 2.0, height / 2.0); //Sets coordinate system to start in 					
	glMatrixMode(GL_MODELVIEW);											//the middle of the screen like a standard graph
	glLoadIdentity();

	// Construction
	Motion motion;
	PlayerObject player(&window, &motion, "Multi-Layer.png", 37, 37);
	BG test(&window);
	test.loadEntity("Wall.txt", "WALL");
	test.loadEntity("Enemy.txt", "BASE_ENEMY");
	test.loadEntity("Medics.txt", "BASE_MEDIC");
	test.loadEntity("MeleeEnemy.txt", "MELEE_ENEMY");
	test.loadEntity("Doors.txt", "DOOR");

	while (!window.closed()){
		window.clear();

		checkForInput(&window, &motion, test); //Getting input values from the player in the current window

		test.update(&motion, &player);

		player.Draw();

		window.update();
		Sleep(0.5); //Controls how fast the game loop runs at max
	}
}
#endif

#if 1

int selectNote(string scaleName);

int main(){
	int width = 50;
	int height = 50;

	glViewport(0, 0, width, height);

	//Changing the in-game window's width and height to something more eye catching
	width = 50;
	height = 50;

	//Game Window
	static Window window("Literally Anything", width, height);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //Game background color

	//OpenGL Coordinate Grid Setup
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-width / 2.0, width / 2.0, -height / 2.0, height / 2.0); //Sets coordinate system to start in 					
	glMatrixMode(GL_MODELVIEW);											//the middle of the screen like a standard graph
	glLoadIdentity();

	while (!window.closed()){
		cout << "What scale would you like to use?\n";
		cout << "1> C Major\n";
		cout << "2> F Major\n";

		int selection;
		cin >> selection;

		cout << "How long would you like to play for?\n";
		cout << "(Please enter a whole number)";

		int duration;
		cin >> duration;

		int passed = 0;

		if (selection == 1){
			//Start Playing on the C Major Scale
			while (passed < duration){
				
				passed += selectNote("C");
			}
			
		}
		else if (selection == 2){
			//Start Playing on the F Major Scale
		}
	}
}

int selectNote(string scaleName){
	sf::Music note;

	int key = rand() % 8 + 1;
	int passed = 0;
	int length = rand() % 8 + 1;
	length *= 500;

	switch (key){
	case 1:
		//Play first note in scale
		note.openFromFile("Resources/Audio/Piano_Tones/c1.ogg");
		break;
	
	case 2:
		//Play second note
		note.openFromFile("Resources/Audio/Piano_Tones/d1.ogg");
		break;
	
	case 3:
		note.openFromFile("Resources/Audio/Piano_Tones/e1.ogg");
		break;
	
	case 4:
		note.openFromFile("Resources/Audio/Piano_Tones/f1.ogg");
		break;

	case 5:
		note.openFromFile("Resources/Audio/Piano_Tones/g1.ogg");
		break;

	case 6:
		note.openFromFile("Resources/Audio/Piano_Tones/a1.ogg");
		break;
	
	case 7:
		note.openFromFile("Resources/Audio/Piano_Tones/b1.ogg");
		break;

	case 8:
		note.openFromFile("Resources/Audio/Piano_Tones/c2.ogg");
		break;

	default:
		cout << "Key was outside of the scale!\n";
		break;
	}
	note.setLoop(true);
	note.play();

	while (passed < length){
		passed++;
	}

	note.stop();

	cout << key << endl;

	return 1;
}

#endif