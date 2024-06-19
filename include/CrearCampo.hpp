#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <iostream>
#include <Celda.hpp>

using namespace sf;
using namespace std;

class CrearCampo
{
public:
    bool ganar = false, perder = false;
    int minast = 0, puntaje = 0;
    Font fuente;
    vector<vector<Celda>> tablero;
    bool ventana = true;
    CrearCampo(int Tam, int minas, int celdas)
    {
        srand(time(0));
        if (!fuente.loadFromFile("assets/fonts/arial.ttf"))
        {

            throw runtime_error("Error al cargar la fuente");
        }
        InicializarTablero(Tam, celdas);
        ColocarMinas(minas, Tam);
    }

private:
    void InicializarTablero(int Tam, int celdas)
    {
        tablero.resize(Tam, vector<Celda>(Tam));
        for (int i = 0; i < Tam; ++i)
        {
            for (int j = 0; j < Tam; ++j)
            {
                tablero[i][j].rect.setSize(Vector2f(celdas - 2, celdas - 2));
                tablero[i][j].rect.setPosition(i * celdas, j * celdas);
                tablero[i][j].rect.setFillColor(Color::Green);
                tablero[i][j].texto.setFont(fuente);
                tablero[i][j].texto.setCharacterSize(24);
                tablero[i][j].texto.setPosition(i * celdas, j * celdas);
            }
        }
    }

    void ColocarMinas(int minas, int Tam)
    {
        minast = minas;
        int minasColocadas = 0;
        while (minasColocadas < minas)
        {
            int x = rand() % Tam;
            int y = rand() % Tam;
            if (!tablero[x][y].tieneMina)
            {
                tablero[x][y].tieneMina = true;
                ++minasColocadas;
            }
        }
    }
};

