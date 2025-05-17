#include <SFML/Graphics.hpp>
#include "../Grid.hpp"
#include "../InputHandler.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Falling Sand");

    //Create grid instance
    //Each particle in this case is 8x8 pixels sowe create a 100x100 grid
    //to match our render window
    Grid grid(100, 100, 8);

    //Create input handler & get the particle size from the grid
    InputHandler input(window, grid.getParticleSize());

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        int gridX, gridY;
        ParticleType placingType;

        input.update();

        if (input.getParticlePlacement(gridX, gridY, placingType)) {
            grid.setParticle(gridX, gridY, placingType);
        }

        //we place a particle in every direction of the actualy particle we are placing
        //this make a 3x3 grid of particles!
        //if (input.getSandPlacement(gridX, gridY)) {
        //    for (int dy = -1; dy <= 1; ++dy) {
        //        for (int dx = -1; dx <= 1; ++dx) {
        //            grid.setParticle(gridX + dx, gridY + dy, ParticleType::Sand);
        //        }
        //    }
        //}

        //Calling update multiple times
        //This increases the "Speed of hpw the particles fall"
        for (int i = 0; i < 2.5; ++i) {
            grid.update();
        }

        window.clear();
        grid.draw(window);
        window.display();
    }

    return 0;
}
