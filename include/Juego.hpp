#pragma once
#include <SFML/Graphics.hpp>   
#include <vector>   
#include <Campo.hpp>
#include <iostream>
#include <Celda.hpp>

using namespace sf;
using namespace std;

class Juego : public Campo
{
public:
    Juego(int Tam, int minas, int celdas) : Campo(Tam, minas, celdas)
    {
    }

    void run(int Tam, int minas, int celdas)
    {
        RenderWindow window(VideoMode(Tam * celdas, Tam * celdas), "Buscaminas SFML");
        while (window.isOpen())
        {

            Event evento;
            while (window.pollEvent(evento))
            {
                if (evento.type == Event::Closed)
                {
                    window.close();
                    ventana = false;
                }
                else if (evento.type == Event::MouseButtonPressed)
                {
                    manejarEventos(window, Tam, celdas);
                }
            }
            window.clear();
            for (int i = 0; i < tablero.size(); i++)
            {
                for (int j = 0; j < tablero[i].size(); j++)
                {
                    window.draw(tablero[i][j].rect);
                    window.draw(tablero[i][j].texto);
                }
            }
            window.display();
            if (ganar || perder)
            {
                RenderWindow estado(VideoMode(200, 200), ganar ? "Ganaste" : "Perdiste");
                Event estado1;
                while (estado.pollEvent(estado1))
                {
                    if (estado1.type == Event::Closed || estado1.type == Event::MouseButtonPressed)
                    {
                        estado.close();
                        window.close();
                    }
                }
                estado.clear();
                estado.display();
            }
        }
    }
    void manejarEventos(RenderWindow &window, int Tam, int celdas)
    {

        Vector2i pos = Mouse::getPosition(window);
        int x = pos.x / celdas;
        int y = pos.y / celdas;
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            revelarCelda(x, y);
        }
        else if (Mouse::isButtonPressed(Mouse::Right))
        {
            colocarBandera(x, y);
        }
    }

private:
    void revelarCelda(int x, int y)
    {
        if (x >= 0 && x < tablero.size() && y >= 0 && y < tablero[0].size() && !tablero[x][y].revelado)
        {
            tablero[x][y].revelado = true;
            if (!tablero[x][y].tieneMina)
            {
                puntaje++;
                int celdasTotales = tablero.size() * tablero[0].size();
                if (puntaje + minast == celdasTotales)
                {
                    cout << "Ganaste";
                    ganar = true;
                }
            }
            int minasCerca = contarMinasCerca(x, y);
            tablero[x][y].minasCerca = minasCerca;
            if (tablero[x][y].tieneMina)
            {
                tablero[x][y].texto.setString("M");
                tablero[x][y].rect.setFillColor(Color::Red);
                perder = true;
            }
            else if (minasCerca > 0)
            {
                tablero[x][y].texto.setString(to_string(minasCerca));
                tablero[x][y].texto.setFillColor(Color::Black);
                tablero[x][y].rect.setFillColor(Color::Yellow);
            }
            else
            {
                tablero[x][y].rect.setFillColor(Color::White);
                for (int dx = -1; dx <= 1; dx++)
                {
                    for (int dy = -1; dy <= 1; dy++)
                    {
                        if (dx == 0 && dy == 0)
                        {
                            continue;
                        }
                        int nx = x + dx;
                        int ny = y + dy;
                        if (nx >= 0 && nx < tablero.size() && ny >= 0 && ny < tablero[0].size())
                        {
                            revelarCelda(nx, ny);
                        }
                    }
                }
            }
        }
    }

    void colocarBandera(int x, int y)
    {
        if (x >= 0 && x < tablero.size() && y >= 0 && y < tablero[0].size() && !tablero[x][y].revelado)
        {
            tablero[x][y].rect.setFillColor(Color::Red);
        }
    }

    int contarMinasCerca(int x, int y)
    {
        int cuenta = 0;
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                int nx = x + i;
                int ny = y + j;
                if (nx >= 0 && nx < tablero.size() && ny >= 0 && ny < tablero[0].size())
                {
                    if (tablero[nx][ny].tieneMina)
                    {
                        cuenta++;
                    }
                }
            }
        }
        return cuenta;
    }
};
