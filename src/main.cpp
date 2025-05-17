#include <SFML/Graphics.hpp>
#include "../Grid.hpp"
#include "../InputHandler.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Falling Sand");

    //Create grid instance
    //Each particle in this case is 8x8 pixels sowe create a 100x100 grid
    //to match our render window
    Grid grid(100, 100, 8);
    InputHandler input(window); //Create input handler

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        int gridX, gridY;
        if (input.getSandPlacement(gridX, gridY)) {
            grid.setParticle(gridX, gridY, ParticleType::Sand);
        }

        window.clear();
        grid.draw(window);
        window.display();
    }

    return 0;
}
