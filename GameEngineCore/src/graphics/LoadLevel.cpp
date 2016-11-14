#include "LoadLevel.h"

namespace spacey{
	namespace level{

		void loadObject(vector<BaseObject> &systemVector, string fileName){
			ifstream file;
			string line, filename, type;
			int width, height, x, y, amount;
			int aux1, aux2;

			file.open(fileName);

			if (file.fail()){ //Check if the file is unavailable
				cout << "Opening file named '" << fileName << "' failed.\n";
			}
			else{ //File is openable
				while (file.is_open()){
					file >> line;

					if (line == "START"){ //Check if keyword is start
						file >> type;

						if (type == "WALL"){
							file >> amount;

							for (int i = 0; i < amount; i++){
								file >> width >> height >> x >> y >> filename; //read the values for the object and add them to the vector

								Wall temp(width, height, x, y, filename);

								systemVector.push_back(temp);
							}
						}
						else if (type == "DOOR"){
							file >> amount;

							for (int i = 0; i < amount; i++){
								file >> x >> y >> width >> height >> aux1 >> aux2 >> filename; //read the values for the object and add them to the vector

								filename = "Resources/Images/" + filename;

								Door temp(x, y, width, height, aux1, aux2, filename);

								systemVector.push_back(temp);
							}
						}
					}
					else if (line == "ENDF"){//Check if the keyword is the end of the file
						cout << "Reached end of file.\n";
						file.close();
					}
				}
			}

		}

		void loadEntity(vector<BaseEntity*> &systemVector, string fileName){
			ifstream file;

			file.open(fileName);

			if (file.fail()){ //Check if the file is openable
				cout << "Opening entity file named '" << fileName << "' failed.\n";
			}
			else{
				string line, filename, type;
				int x, y, amount, texWidth, texHeight;

				while (file.is_open()){
					file >> line;

					if (line == "START"){ //Check if keyword is start
						file >> type;

						if (type == "BASE_ENEMY"){
							file >> amount;

							for (int i = 0; i < amount; i++){
								file >> x >> y >> texWidth >> texHeight >> filename; //read the values for the object and add them to the vector

								filename = "Resources/Images/" + filename;

								BaseEnemy temp(x, y, texWidth, texHeight, filename);

								systemVector.push_back(&temp);
							}
						}
						else if (type == "MELEE_ENEMY"){
							file >> amount;

							for (int i = 0; i < amount; i++){
								file >> x >> y >> texWidth >> texHeight >> filename; //read the values for the object and add them to the vector

								filename = "Resources/Images/" + filename;

								MeleeEnemy temp(x, y, texWidth, texHeight, filename);

								systemVector.push_back(&temp);
							}
						}
						else if (type == "BASE_MEDIC"){
							file >> amount;

							for (int i = 0; i < amount; i++){
								file >> x >> y >> texWidth >> texHeight >> filename; //read the values for the object and add them to the vector

								filename = "Resources/Images/" + filename;

								BaseMedic temp(x, y, texWidth, texHeight, filename);

								systemVector.push_back(&temp);
							}
						}
					}
					else if (line == "ENDF"){//Check if the keyword is the end of the file
						cout << "Reached end of file.\n";
						file.close();
					}
				}
			}

		}
	}

}