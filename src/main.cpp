
#include <iostream>
#include <SFML/Graphics.hpp>
#include <format>
#include <button.hpp>
#include <emmett.hpp>

int main()
{
    std::shared_ptr<Emmett> emmett = std::make_shared<Emmett>();

    sf::RenderWindow window(sf::VideoMode(1600, 900), "SuperEMMETT");

    sf::Font font;
    if (!font.loadFromFile("assets/RifficFree-Bold.ttf"))
        return -1;

    sf::Clock clock;
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        emmett->_mouse.update(window);
        emmett->update(deltaTime, emmett);
        emmett->draw(window);
    }
}