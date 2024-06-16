#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


using namespace std;
using namespace sf;
class Facil {
public:
    bool ventana = true;
    Facil() {
        RenderWindow window(sf::VideoMode(600, 600), "Facil");
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                ventana = false;
            }
            window.clear();
            window.display();
        }
        
    }
};