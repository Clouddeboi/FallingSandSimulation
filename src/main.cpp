#include <SFML/Graphics.hpp>
#include "../Grid.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Falling Sand");

    //Create grid instance
    //Each particle in this case is 8x8 pixels sowe create a 100x100 grid
    //to match our render window
    Grid grid(100, 100, 8);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        grid.draw(window);
        window.display();
    }

    return 0;
}
