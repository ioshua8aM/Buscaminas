#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <Campo.hpp>
#include <iostream>
#include <Celda.hpp>
#include <Juego.hpp>

using namespace sf;
using namespace std;   

class Dificultad
{
public:
    bool seleccion;
    Dificultad(int tam, int minas, int celdas)
    {
        Juego juego(tam, minas, celdas);
        Campo campo(tam, minas, celdas);
        juego.run(tam, minas, celdas);
        seleccion = true;
    }
};
