#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

const int TAM = 10; // Tamaño del tablero (TAM x TAM)
const int CELDA = 60; // Tamaño de cada celda en píxeles
const int MINAS = 20; // Número total de minas

// Estructura para representar cada celda del tablero
struct Celda {
    RectangleShape rect;
    Text texto;
    bool tieneMina = false;
    bool revelado = false;
    int minasCerca = 0;
};

class Campo {
public:
    Campo() {
        srand(time(0)); // Inicializar la semilla del generador de números aleatorios
        if (!fuente.loadFromFile("arial.ttf")) {
            throw runtime_error("Error al cargar la fuente");
        }
        inicializarTablero();
        colocarMinas();
    }

    void run() {
        
        RenderWindow window(VideoMode(TAM * CELDA, TAM * CELDA), "Buscaminas SFML");
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();
            }

            window.clear();
            // Dibujar tablero
            for (int i = 0; i < TAM; ++i) {
                for (int j = 0; j < TAM; ++j) {
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

    void inicializarTablero() {
        tablero.resize(TAM, vector<Celda>(TAM));
        for (int i = 0; i < TAM; ++i) {
            for (int j = 0; j < TAM; ++j) {
                tablero[i][j].rect.setSize(Vector2f(CELDA - 2, CELDA - 2));
                tablero[i][j].rect.setPosition(i * CELDA, j * CELDA);
                tablero[i][j].rect.setFillColor(Color::Green);
                tablero[i][j].texto.setFont(fuente);
                tablero[i][j].texto.setCharacterSize(24);
                tablero[i][j].texto.setPosition(i * CELDA, j * CELDA);
            }
        }
    }

    void colocarMinas() {
        int minasColocadas = 0;
        while (minasColocadas < MINAS) {
            int x = rand() % TAM;
            int y = rand() % TAM;
            if (!tablero[x][y].tieneMina) {
                tablero[x][y].tieneMina = true;
                ++minasColocadas;
            }
        }
    }
};
