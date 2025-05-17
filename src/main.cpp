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

        if (input.shouldClearGrid()) {
            grid.clear();
        }

        if (input.getParticlePlacement(gridX, gridY, placingType)) {
            if (placingType == ParticleType::Sand) {
                //Place Sand in a 3x3 grid
                for (int dy = -1; dy <= 1; ++dy) {
                    for (int dx = -1; dx <= 1; ++dx) {
                        int x = gridX + dx;
                        int y = gridY + dy;

                        if (grid.getParticleType(x, y) == ParticleType::Empty) {
                            grid.setParticle(x, y, ParticleType::Sand);
                        }
                    }
                }
            }
            else if (placingType == ParticleType::Water) {
                //Place Water in a circular area only on empty cells
                for (int dy = -2; dy <= 2; ++dy) {
                    for (int dx = -2; dx <= 2; ++dx) {
                        if (dx * dx + dy * dy <= 4) {
                            int x = gridX + dx;
                            int y = gridY + dy;

                            if (grid.getParticleType(x, y) == ParticleType::Empty) {
                                grid.setParticle(x, y, ParticleType::Water);
                            }
                        }
                    }
                }
            }
            else {
                // For other particles, place only on empty cells
                if (grid.getParticleType(gridX, gridY) == ParticleType::Empty) {
                    grid.setParticle(gridX, gridY, placingType);
                }
            }
        }

        //Calling update multiple times
        //This increases the "Speed of hpw the particles fall"
        for (int i = 0; i < 2; ++i) {
            grid.update();
        }

        window.clear();
        grid.draw(window);
        window.display();
    }

    return 0;
}
