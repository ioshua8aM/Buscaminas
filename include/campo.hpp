#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <iostream>

using namespace sf;
using namespace std;


struct Celda
{
    RectangleShape rect;
    Text texto;
    bool tieneMina = false;
    bool revelado = false;
    int minasCerca = 0;
    bool derrota = false;
};

class Campo
{
public:
    int minast = 0, puntaje = 0;
    bool derrota = false, victoria = false;
    Font fuente;
    vector<vector<Celda>> tablero;
    bool ventana = true;
    Campo(int Tam, int minas, int celdas)
    {
        srand(time(0));
        if (!fuente.loadFromFile("include/arial.ttf"))
        {
            
            throw runtime_error("Error al cargar la fuente");
        }
        inicializarTablero(Tam, celdas);
        colocarMinas(minas, Tam);
    }

private:

    void inicializarTablero(int Tam, int celdas)
    {
        tablero.resize(Tam, vector<Celda>(Tam));
        for (int i = 0; i < Tam; ++i)
        {
            for (int j = 0; j < Tam; ++j)
            {
                // Proper initialization of SFML objects
                tablero[i][j].rect.setSize(Vector2f(celdas - 2, celdas - 2));
                tablero[i][j].rect.setPosition(i * celdas, j * celdas);
                tablero[i][j].rect.setFillColor(Color::Green);
                tablero[i][j].texto.setFont(fuente);
                tablero[i][j].texto.setCharacterSize(24);
                tablero[i][j].texto.setPosition(i * celdas, j * celdas);
            }
        }
    }

    void colocarMinas(int minas, int Tam)
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

class Juego : public Campo
{
public:
    Juego(int Tam, int minas, int celdas) : Campo(Tam, minas, celdas)
    {
    }

    void run(int Tam, int minas, int celdas)
    {
        RenderWindow window(VideoMode(Tam * celdas, Tam * celdas), "Buscaminas SFML");
        RenderWindow perdiste(VideoMode(400, 400), "Perdiste");
        Text texto;
        texto.setFont(fuente);
        texto.setString("Perdiste");
        texto.setCharacterSize(24);
        texto.setFillColor(Color::White);
        texto.setPosition(50, 50);
        RenderWindow ganaste(VideoMode(400, 400), "Ganaste");
        Text texto1;  
        texto1.setFont(fuente);
        texto1.setString("Ganaste");
        texto1.setCharacterSize(24);
        texto1.setFillColor(Color::White);
        texto1.setPosition(50, 50);        
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
            }
            manejarEventos(window, Tam, celdas);

            if (derrota == true)
            {
                perdiste.clear();
                perdiste.draw(texto);
                perdiste.display();
                ventana = false;
            }

            if (victoria == true)
            {
                ganaste.clear();
                ganaste.draw(texto1);
                ganaste.display();
                ventana = false;
            }
            window.display();
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
            if (tablero[x][y].derrota)
            {
                derrota = true;
            }
            if (puntaje == (tablero.size()*tablero[0].size()-minast))
            {
                victoria = true;
            }
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
            if(!tablero[x][y].tieneMina)
            {
                puntaje++;
            }
            int minasCerca = contarMinasCerca(x, y);
            tablero[x][y].minasCerca = minasCerca;
            if (tablero[x][y].tieneMina)
            {
                tablero[x][y].derrota = true;
                tablero[x][y].texto.setString("M");
                tablero[x][y].rect.setFillColor(Color::Red);
            }
            else if(minasCerca > 0)
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
            // Simplemente cambiamos el color para indicar una bandera, en un juego real se debería gestionar mejor
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
