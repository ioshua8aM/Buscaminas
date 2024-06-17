#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

using namespace sf;
using namespace std;

const int CELDA = 60; // Tamaño de cada celda en píxeles

struct Celda {
    RectangleShape rect;
    Text texto;
    bool tieneMina = false;
    bool revelado = false;
    int minasCerca = 0;
};

class Campo {
public:
    bool ventana = true;
    Campo(int Tam, int minas, int celdas) {
        srand(time(0)); // Correct usage for basic randomness
        if (!fuente.loadFromFile("include/arial.ttf")) {
            // Ensure the path is correct and accessible
            throw runtime_error("Error al cargar la fuente");
        }
        inicializarTablero(Tam, celdas);
        colocarMinas(minas, Tam); // Ensure parameters are in the correct order
    }

    void run(int Tam, int celdas) {
        RenderWindow window(VideoMode(Tam * celdas, Tam * celdas), "Buscaminas SFML");
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                {
                    window.close();
                    ventana = false;
                }
            }

            window.clear();
            for (int i = 0; i < Tam; ++i) {
                for (int j = 0; j < Tam; ++j) {
                    window.draw(tablero[i][j].rect);
                    if (tablero[i][j].revelado) {
                        window.draw(tablero[i][j].texto);
                    }
                }
            }
            window.display();
        }
    }

private:

    vector<vector<Celda>> tablero;
    Font fuente;

    void inicializarTablero(int Tam, int celdas) {
        tablero.resize(Tam, vector<Celda>(Tam));
        for (int i = 0; i < Tam; ++i) {
            for (int j = 0; j < Tam; ++j) {
                // Proper initialization of SFML objects
                tablero[i][j].rect.setSize(Vector2f(celdas - 2, celdas - 2));
                tablero[i][j].rect.setPosition(i * celdas, j * celdas);
                tablero[i][j].rect.setFillColor(Color::Green);
                tablero[i][j].texto.setFont(fuente); // Ensure font is loaded before this point
                tablero[i][j].texto.setCharacterSize(24);
                tablero[i][j].texto.setPosition(i * celdas, j * celdas);
            }
        }
    }

    void colocarMinas(int minas, int Tam) {
        int minasColocadas = 0;
        while (minasColocadas < minas) {
            int x = rand() % Tam;
            int y = rand() % Tam;
            if (!tablero[x][y].tieneMina) {
                tablero[x][y].tieneMina = true;
                ++minasColocadas;
            }
        }
    }
};