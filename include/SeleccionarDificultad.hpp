#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <CrearCampo.hpp>
#include <iostream>
#include <Celda.hpp>
#include <Jugar.hpp>

using namespace sf;
using namespace std;   

class SeleccionarDificultad
{
public:
    bool seleccion;
    SeleccionarDificultad(int tam, int minas, int celdas)
    {
        Jugar juego(tam, minas, celdas);
        CrearCampo campo(tam, minas, celdas);
        juego.Ejecutar(tam, minas, celdas);
        seleccion = true;
    }
};
