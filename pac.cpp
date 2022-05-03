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
template<typename T>

bool inrange(T x1, T x2, T x3, T x4) {//this function will return true if var 1 to xar 2 are within range of var 3 to var 4
	//will not pass an error if the char is equal lol 

	if (x1 == x3 || x2 == x3 || x1 == x4 || x2 == x4) return true;
	else if (x1 > x2) {
		if (x3<x1 and x3>x2 || x3 == x1 || x3 == x2) return true;
		else if (x4<x1 and x4 >x2) return true;
	}
	else if (x2 > x1) {
		if (x3<x2 and x3>x1) return true;
		else if (x4<x2 and x4 >x1 || x4 == x1 || x4 == x2) return true;
	}
	else {
		return false;
	}


}
struct points {
	float x; float y;
};
int main()
{
	points maptemp[4];
	points plyr[4];
	square Player(xpos,ypos,2,40,true,sf::Color::Red);//funkin player 
	//funking stupid struct :( :(:( :( this code is painful :(:( 

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

			map[x].push_back(new square(80 * x +40, 80 * f + 40, 2.0, 40, true, sf::Color::Blue));//bounderies of map
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

		
		screen.clear(sf::Color::Black);
		plyr[0] = { Player.x - Player.f , Player.y - Player.ydil };
		plyr[1] = { Player.x + Player.f , Player.y - Player.ydil };
		plyr[2] = { Player.x + Player.f , Player.y + Player.ydil };
		plyr[3] = { Player.x - Player.f , Player.y + Player.ydil };
		for (int cols = 0; cols < 10; cols++) {
			for (int rows = 0; rows < 10; rows++) {
				
				if (map[cols][rows]->type == 1) {
					
					maptemp[0] = { map[cols][rows]->x - map[cols][rows]->f,  map[cols][rows]->y - map[cols][rows]->ydil };//a
					maptemp[1] = { map[cols][rows]->x + map[cols][rows]->f,  map[cols][rows]->y - map[cols][rows]->ydil };//b
					maptemp[2] = { map[cols][rows]->x + map[cols][rows]->f,  map[cols][rows]->y + map[cols][rows]->ydil };//c
					maptemp[3] = { map[cols][rows]->x - map[cols][rows]->f,  map[cols][rows]->y + map[cols][rows]->ydil };//d
					
					if (maptemp[1].x>plyr[0].x and inrange<float>(maptemp[2].y, maptemp[3].y, plyr[0].y, plyr[3].y) == true) {
						std::cout << "collision\n"; std::cout<<std::endl;
						keys[LEFT] = false;
						
					}
					if (inrange<float>(maptemp[0].x, maptemp[3].x, plyr[0].x, plyr[3].x) == true and inrange<float>(maptemp[1].y, maptemp[3].y, plyr[0].y, plyr[3].y) == true) {
						std::cout << "collision\n"; std::cout << std::endl;
						keys[LEFT] = false;
					}
					//fucking gross :(
					
					//fuckin cycles through because i said so 


					map[cols][rows]->draw(screen);
				}

				
			}
			
		}
		Player.x += vx;
		Player.y += vy;

		Player.update();
		Player.draw(screen);
		screen.display();
	}

}

