#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <C:\Users\user\Desktop\Buscaminas\include\campo.hpp>

using namespace std;
using namespace sf;

    class Facil {
private:
   RenderWindow& window;
    

public:
    Facil(RenderWindow& win) : window(win) {}
    bool ventana = true;
    void runf() {
        cout << "Facil" << endl;
        while (window.isOpen()) 
        {
            Event event;
            while (window.pollEvent(event)) {   
                if (event.type == sf::Event::Closed) {
                    window.close();
                    ventana = false;
                }
            }
            Campo campo;
        campo.run();
        }
        cout << "llamando a campo" << endl; 
        
    }
};