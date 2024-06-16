#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <C:\Users\user\Desktop\Buscaminas\include\campo.hpp>

using namespace std;
using namespace sf;
class Inetermedio {
public:
    bool ventana = true;
    Inetermedio() {
        RenderWindow window(sf::VideoMode(600, 600), "Intermedio");
        while (window.isOpen())
        {
            Campo campo;
            campo.run();
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