#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

struct Celda
{
    RectangleShape rect;
    Text texto;
    bool tieneMina = false;
    bool revelado = false;
    int minasCerca = 0;
};