
#include <iostream>
#include <SFML/Graphics.hpp>
#include <code.hpp>

int main()
{
    std::cout << "SuperEMMETT started." << std::endl;
    Code code;

    for (int i = 0; i < 10; i += 1) {
        code.lines.emplace_back();
        std::cout << "Line " << i + 1 << " created." << std::endl;
    }

    sf::RenderWindow window(sf::VideoMode(1600, 900), "SuperEMMETT");
    sf::RectangleShape rectangle(sf::Vector2f(100, 20));
    rectangle.setFillColor({250, 250, 250});
    rectangle.setPosition(100, 100);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }



        window.clear();

        int offset = 0;
        for (auto &l : code.lines)
        {
            rectangle.setPosition(1400, 100 + offset);
            window.draw(rectangle);
            offset += 30; // Increment offset for each line
        }

        window.display();
    }
}