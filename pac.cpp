#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <complex>// using for the points of obj sqaures 


#include "square.h"
const int PACSIZE = 35;
const int WALLSIZE = 80;
enum DIRECTIONS { LEFT, RIGHT, UP, DOWN }; //left is 0, right is 1, up is 2, down is 3
bool keys[] = { false, false, false, false }; //array to hold keyboard input

int dir;
bool recentx;
bool recenty;
int xpos = 100;
int ypos = 100;
int vx = 0;
int vy = 0;

int temp = NULL;
// im putting ALL my functions up here on the top, because that's where i am, at the fuckin top of the goddammed world !!!!:) jk no this code is ass 
// and makes me want to go home :(
template <typename t> bool inrange(t x1, t x2, t y1, t y2) {
	if (x1 > x2) {
		if (y1 > x1 and y2 < x2) return true;
		else if (y2 <x1 and y2 >x2) return true;
		else return false;
	}
	else if (x2 > x1) {
		if (y1<x1 and y2 >x2) return true;
		else if (y2 <x1 and y2 >x2) return true;
		else return false;

	}
	else if (x1 == x2) {
		if (x1 == y1 or x1 == y2) return true;
		else return false;
	}

	// no else because i fuckin said so 
};
struct points {
	float x1; float x2;
};





int main()
{
	points maptemp[4];
	points plyr[2];
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
				dir = LEFT;
			}
			else keys[LEFT] = false;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				keys[RIGHT] = true;
				dir = RIGHT;
			}
			else keys[RIGHT] = false;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				keys[UP] = true;
				dir = UP;
			}
			else keys[UP] = false;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				keys[DOWN] = true;
				dir = DOWN;
			}
			else keys[DOWN] = false;


		}//end event loop---------------------------------------------------------------
		screen.clear(sf::Color::Black);
		plyr[0] = { Player.x + Player.f,   Player.x - Player.f };//x range 
		plyr[1] = { Player.y + Player.ydil,   Player.y - Player.ydil };//y range 
		temp = NULL;
		for (int cols = 0; cols < 10; cols++) {
			for (int rows = 0; rows < 10; rows++) {
				if (map[cols][rows]->type == 1) {
					maptemp[0] = { (map[cols][rows]->x + map[cols][rows]->f), (map[cols][rows]->x - map[cols][rows]->f) };//a x1 - x2
					maptemp[1] = { (map[cols][rows]->y + map[cols][rows]->ydil),  (map[cols][rows]->y - map[cols][rows]->ydil) };//b y1 - y2
					if (inrange(plyr[0].x1, plyr[0].x2, maptemp[0].x1, maptemp[0].x2) and inrange(plyr[1].x1, plyr[1].x2, maptemp[1].x1, maptemp[1].x2)) {
						std::cout << "collision\n";
						dir[keys] = false;
					}
					else {
						std::cout << "not col\n";
					}
					map[cols][rows]->draw(screen);
				}
			}

		}
		//SETTING Mr. Pac's velocity
		if (keys[LEFT] == true)
		{
			vx = -5; recentx = 0;
		}
		
		else if (keys[RIGHT] == true)
		{
			vx = 5; recentx = 1;
		}
		else vx = 0; recentx = NULL;
		if (keys[UP] == true)
		{
			vy = -5;
			recenty = 0;
		}
		else if (keys[DOWN] == true)
		{
			vy = 5;
			recenty = 1;

		}
		
		else { vy = 0; recenty = NULL; }// The laws of momentum do not apply to Mr. Pac
		// I/O ---------------------

		
		
		
		Player.x += vx;
		Player.y += vy;

		Player.update();
		Player.draw(screen);
		screen.display();
	}

}

