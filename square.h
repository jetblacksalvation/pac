#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>



class square {
public:             // Access specifier
    int x;
    int y;          // Attribute (int variable)
    float dial;
    float f;
    float ydil;
    float frmOrigin;
    int type;
    sf::Color colder;
    sf::VertexArray linesCenter;
    sf::VertexArray linesLeft;
    
    //default constructor
    square(){

        x = 0;
        y = 0;
        f = 0;
        dial = 0;
        frmOrigin = true;
        ydil = 0;
        colder = sf::Color::White;
    };

    //paramaterized constructor
    square(int xpos, int ypos, float dialation, float fdis, bool origi,sf::Color colours) {
        x = xpos;
        y = ypos;
        dial = dialation;
        f = fdis;
        frmOrigin = origi;

        
        colder = colours;
        ydil = (sqrt(dial * pow(f, 2) - pow(f, 2)))/2;//this is because the size of the shape is twice of that of top left origin 

        
        
        

        linesCenter.setPrimitiveType(sf::PrimitiveType::Quads);

        linesCenter.append(sf::Vertex(sf::Vector2f(x - f, y - ydil ), colours));
        linesCenter.append(sf::Vertex(sf::Vector2f(x + f, y - ydil ), colours));
        linesCenter.append(sf::Vertex(sf::Vector2f(x + f, y + ydil ), colours));
        linesCenter.append(sf::Vertex(sf::Vector2f(x - f, y + ydil), colours));

        linesLeft.setPrimitiveType(sf::PrimitiveType::Quads);

        linesLeft.append(sf::Vertex(sf::Vector2f(x, y), colours));
        linesLeft.append(sf::Vertex(sf::Vector2f(x + f, y), colours));
        linesLeft.append(sf::Vertex(sf::Vector2f(x + f, y + ydil), colours));
        linesLeft.append(sf::Vertex(sf::Vector2f(x, y + ydil), colours));
    }
    void update() {
        if (frmOrigin == true) {
            linesCenter[0].position = sf::Vector2f(x - f / 2, y - ydil ),colder;
            linesCenter[1].position = sf::Vector2f(x + f / 2, y - ydil ),colder;
            linesCenter[2].position = sf::Vector2f(x + f / 2, y + ydil ),colder;
            linesCenter[3].position = sf::Vector2f(x - f / 2, y + ydil ),colder;
        }
        else {

            linesLeft[0].position = sf::Vector2f(x, y), colder;
            linesLeft[1].position = sf::Vector2f(x + f, y), colder;
            linesLeft[2].position = sf::Vector2f(x + f, y + ydil), colder;
            linesLeft[3].position = sf::Vector2f(x, y + ydil), colder;
        }

    }
    void verupdate() {

    };
    void add(int xs, int ys) {
        x += xs;
        y += ys;

    }
    void setorigin(int xs, int ys) {
        x = xs;
        y = ys;
    }
    void draw(sf::RenderWindow& wind) {
        if (frmOrigin == true) {
            wind.draw(linesCenter);
        }
        else {
            wind.draw(linesLeft);
        }

    }


};