#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <complex>// using for the points of obj sqaures 

#include "square.h"
const int PACSIZE = 35;
const int WALLSIZE = 80;
enum DIRECTIONS { LEFT, RIGHT, UP, DOWN }; //left is 0, right is 1, up is 2, down is 3
bool keys[] = { false, false, false, false }; //array to hold keyboard input

int xpos = 100;
int ypos = 100;
int vx = 0;
int vy = 0;

struct points {
	float x; float y;
};
int main()
{
	points maptemp[4];
	points plyr[4];
	square Player(xpos,ypos,2,40,false,sf::Color::Red);//fukin player 
	//fucking stupid struct :( :(:( :( this code is painful :(:( 

	std::vector<std::vector<square*>> map;//wierd shi that i got to work with the help of critical hex
	std::vector<square*> extra;//4 sum reason needs a variable that is a ptr and not something else i thinks it's because it needs a pointer and a reference ?
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

	//getting index errors, how tho? it should not be getting index bound errors ?????? i have very similar code that works in a seperate program - fixed thnx critical hex 
	for (int x = 0; x < 10; x++) {
		map.push_back(extra);
		for (int f = 0; f < 10; f++) {

			map[x].push_back(new square(80 * x +40, 80 * f + 40, 2.0, 80, true, sf::Color::Blue));//bounderies of map
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
		plyr[0] = { Player.x - Player.f , Player.y - Player.ydil };
		plyr[1] = { Player.x - Player.f , Player.y - Player.ydil };
		plyr[2] = { Player.x + Player.f , Player.y + Player.ydil };
		plyr[3] = { Player.x - Player.f , Player.y + Player.ydil };
		Player.x += vx;
		Player.y += vy;
		screen.clear(sf::Color::Black);

		for (int cols = 0; cols < 10; cols++) {
			for (int rows = 0; rows < 10; rows++) {
				
				if (map[cols][rows]->type == 1) {
					
					maptemp[0] = { map[cols][rows]->x - map[cols][rows]->f,  map[cols][rows]->y - map[cols][rows]->ydil };//a
					maptemp[1] = { map[cols][rows]->x + map[cols][rows]->f,  map[cols][rows]->y - map[cols][rows]->ydil };//b
					maptemp[2] = { map[cols][rows]->x + map[cols][rows]->f,  map[cols][rows]->y + map[cols][rows]->ydil };//c
					maptemp[3] = { map[cols][rows]->x - map[cols][rows]->f,  map[cols][rows]->y + map[cols][rows]->ydil };//d
					
					for (int x = 0; x < 4; x++) {
						for (int f = 0; f < 4; f++) {
							if (plyr[f].x < maptemp[x].x) {

								if (x == 3) {
									keys[LEFT] = false;
								}
								if (x == 2) {
									keys[RIGHT] = false;
								}

								if (x == 1) {
									keys[RIGHT] = false;
								}
								else if (x == 0) {
									keys[LEFT] = false;


								}

							}
							if (plyr[f].y <= maptemp[x].y) {
								if (x == 2 or x ==4) {
									keys[UP] = false;

								}
								else if (x == 0 or x ==3) {
									keys[DOWN] = false;
								}
							}
						}


					}
					//fucking gross :(
					
					//fuckin cycles through because i said so 


					map[cols][rows]->draw(screen);
				}

				
			}
			
		}
		
		Player.update();
		Player.draw(screen);
		screen.display();
	}

}

