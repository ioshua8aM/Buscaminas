#include <SFML/Graphics.hpp>
#include <Campo.hpp>
#include <Dificultad.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace sf;

int main()
{
    // Crear un botón
    vector<RectangleShape> botones;

    // Crear una ventana de SFML
    RenderWindow window(VideoMode(600, 600), "Buscaminas");

    // Crear opciones de menú
    vector<string> Opciones = {"Facil", "Intermedio", "Dificil"};

    Font letra;
    if (!letra.loadFromFile("assets/fonts/arial.ttf"))
    {
        cout << "Could not load font" << endl;
        return 1;
    }

    Text texto;
    texto.setFont(letra);
    texto.setString("Bienvendio a Buscaminas \nSelecciona una difcultad: \n\n");
    texto.setCharacterSize(24);
    texto.setFillColor(Color::White);
    texto.setPosition(50.f, 50.f);

    vector<Text> menu;
    for (int i = 0; i < Opciones.size(); i++)
    {
        Text texto1;
        texto1.setFont(letra);
        texto1.setString(Opciones[i]);
        texto1.setCharacterSize(24);
        texto1.setFillColor(Color::White);
        texto1.setPosition(50.f, 120.f + i * 50.f);
        menu.push_back(texto1);

        RectangleShape button(Vector2f(200.f, 50.f));
        button.setFillColor(Color::Transparent);
        button.setPosition(50.f, 120.f + i * 50.f);
        botones.push_back(button);
    }

    bool seleccion = false;
    while (window.isOpen())
    {
        Event evento;
        while (window.pollEvent(evento))
        {
            if (evento.type == Event::Closed)
            {
                window.close();
            }
            // Posicion del mouse
            Vector2i mousePos = Mouse::getPosition(window);

            int x = 1, i = 0;
            for (i; i < botones.size(); i++)
            {
                if (botones[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    menu[i].setStyle(Text::Underlined);
                }
                else
                {
                    menu[i].setStyle(Text::Regular);
                }

                if (evento.type == Event::MouseButtonPressed)
                {
                    if (botones[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        if (i == 0)
                        {
                            Dificultad facil(10, 10, 60);
                            seleccion = true;

                        }
                        if (i == 1)
                        {
                            Dificultad intermedio(20, 40, 30);
                            seleccion = true;
                        }
                        if (i == 2)
                        {
                            Dificultad dificil(30, 100, 10);
                            seleccion = true;
                        }
                    }
                }
            }
        }

        window.clear();

        window.draw(texto);

        for (const auto &text : menu)
        {
            window.draw(text);
        }

        window.display();
    }
    if (seleccion == true)
    {
        window.close();
    }

    return 0;
}