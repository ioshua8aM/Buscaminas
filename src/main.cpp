#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    // Crear un botón
    sf::RectangleShape button(sf::Vector2f(50.f, 50.f));

    // Crear una ventana de SFML
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");

    // Crear opciones de menú
    vector<string> menuOptions = {"Option 1", "Option 2", "Option 3"};

    sf::Font font;
    if (!font.loadFromFile("include/arial.ttf"))
    {
        cout << "Could not load font" << endl;
        return 1;
    }

    vector<sf::Text> menuTexts;
    for (int i = 0; i < menuOptions.size(); i++)
    {
        sf::Text text;
        text.setFont(font);
        text.setString("Bienvendio a Buscaminas \n");
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setPosition(50.f, 50.f);
        menuTexts.push_back(text);

        sf::Text text1;
        text1.setFont(font);
        text1.setString(menuOptions[i]);
        text1.setCharacterSize(24);
        text1.setFillColor(sf::Color::White);
        text1.setPosition(50.f, 80.f + i * 50.f);
        menuTexts.push_back(text1);

        button.setFillColor(sf::Color::Green);
        button.setPosition(50.f, 250.f);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (const auto &text : menuTexts)
        {
            window.draw(text);
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                // mouse position (relative to window)
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                //cout << "Mouse position: " << mousePos.x << ", " << mousePos.y << endl;

                if (button.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    button.setFillColor(sf::Color::Red);
                }
                else
                {
                    button.setFillColor(sf::Color::Green);
                }
            }
        }
        for (const auto &text : menuTexts)
        {
            window.draw(text);
        }
        window.draw(button);
        window.display();
    }

    return 0;
}
