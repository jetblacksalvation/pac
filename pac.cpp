#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>


#include "square.h"
const int PACSIZE = 35;
const int WALLSIZE = 80;
enum DIRECTIONS { LEFT, RIGHT, UP, DOWN }; //left is 0, right is 1, up is 2, down is 3
bool keys[] = { false, false, false, false }; //array to hold keyboard input

int xpos = 85;
int ypos = 85;
int vx = 0;
int vy = 0;
int main()
{
	
	square Player(xpos,ypos,2,40,false,sf::Color::Red);//fukin player 

	std::vector<std::vector<square*>> map;//wierd shi that i got to work with the help of critical hex
	std::vector<square*> extra;//4 sum reason needs a variable that is a ptr and not something else 
	const float FPS = 60.0f; //FPS
	
	int compare[10][10] = { //projecting the map onto the above vector, this is like the least efficient way to do this 
	 1,1,1,1,1,1,1,1,1,1,
	 1,0,0,0,0,0,0,0,0,1,
	 1,0,1,1,1,0,1,1,0,1,
	 1,0,1,0,0,0,1,0,0,1,
	 1,0,0,0,1,1,0,0,1,1,
	 1,1,0,0,0,1,0,0,0,1,
	 1,0,0,1,0,0,0,1,0,1,
	 1,0,1,1,1,0,1,1,0,1,
	 1,0,0,0,0,0,0,0,0,1,
	 1,1,1,1,1,1,1,1,1,1
	};

	//getting index errors, how tho? it should not be getting index bound errors ?????? i have very similar code that works in a seperate program
	for (int x = 0; x < 10; x++) {
		map.push_back(extra);
		for (int f = 0; f < 10; f++) {

			map[x].push_back(new square(80 * x , 80 * f , 2.0, 80, false,sf::Color::Blue));//bounderies of map
			if (compare[x][f] == 1) {
				map[x][f]->type = 1;
			}
			map[x][f]->update();
		}

	}


	


	sf::RenderWindow screen(sf::VideoMode(800, 800), "pacman"); //set up screen
	screen.setFramerateLimit(FPS); //set FPS
	sf::Event event; //set up event queue
	std::cout << "Hello Pacman!\n";

	while (screen.isOpen()) {//keep window open until user shuts it down

		while (screen.pollEvent(event)) { //look for events-----------------------

			//this checks if the user has clicked the little "x" button in the top right corner
			if (event.type == sf::Event::EventType::Closed)
				screen.close();
			//KEYBOARD INPUT 
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				keys[LEFT] = true;
			}
			else keys[LEFT] = false;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				keys[RIGHT] = true;
			}
			else keys[RIGHT] = false;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				keys[UP] = true;
			}
			else keys[UP] = false;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				keys[DOWN] = true;
			}
			else keys[DOWN] = false;


		}//end event loop---------------------------------------------------------------

		//SETTING Mr. Pac's velocity
		if (keys[LEFT] == true)
			vx = -5;

		else if (keys[RIGHT] == true)
			vx = 5;

		else vx = 0;
		if (keys[UP] == true)
			vy = -5;

		else if (keys[DOWN] == true)
			vy = 5;

		else vy = 0; // The laws of momentum do not apply to Mr. Pac
		// I/O ---------------------
		Player.x += vx;
		Player.y += vy;
		screen.clear(sf::Color::Black);

		for (int cols = 0; cols < 10; cols++) {
			for (int rows = 0; rows < 10; rows++) {
				
				if (map[cols][rows]->type == 1) {

					map[cols][rows]->draw(screen);
				}
				//very shity collision it's so bad :(
				if (Player.x+Player.f>=map[cols][rows]->x){//right collison
					 keys[RIGHT] = false; 
					 Player.colder = sf::Color::Green;
					 std::cout << "collision\n";
				}
				if (Player.x  <= map[cols][rows]->x+map[cols][rows]->f) {//left
					keys[LEFT] = false;
					Player.colder = sf::Color::Green;
					std::cout << "collision\n";
				}
				//if () {//up
				//	keys[UP] = false;
				//	Player.colder = sf::Color::Green;
				//	std::cout << "collision\n";

				//}
				//	
				//if () {//down
				//	keys[DOWN] = false;
				//	Player.colder = sf::Color::Green;
				//	std::cout << "collision\n";
				//}
				//

				
			}
			
		}
		
		Player.update();
		Player.draw(screen);
		screen.display();
	}

}

