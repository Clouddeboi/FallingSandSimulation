#include "Grid.hpp"

using namespace std;

//Constructor initializes the grid with empty particles
Grid::Grid(int width, int height, int particleSize)
    : width(width), height(height), particleSize(particleSize)
{
    //Initialize the 2D particle grid with empty particles
    particles = vector<vector<Particle>>(height, vector<Particle>(width));
}

int Grid::getParticleSize() const {
    return particleSize;
}

//Draw function that loops through the grid and draws each particle as a square
void Grid::draw(sf::RenderWindow& window) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Particle& p = particles[y][x];

            //Creates a square shape for the particle
            sf::RectangleShape shape(sf::Vector2f(particleSize, particleSize));
            //Sets Position according to grid coordinates
            shape.setPosition(x * particleSize, y * particleSize);
            //Set the fill colour depending on the particle type/colour
            shape.setFillColor(p.color);

            //Draw the shape to the window
            window.draw(shape);
        }
    }
}

void Grid::setParticle(int x, int y, ParticleType type) {
    //Check the grid bounds
    if (x < 0 || x >= width || y < 0 || y >= height)
        return;

    particles[y][x].type = type;

    //set the colour based on the type of particle (Sand)
    if (type == ParticleType::Sand)
        particles[y][x].color = sf::Color(194, 178, 128);//Sandy Colour?
    else
        particles[y][x].color = sf::Color::Black;//Else just make it black
}
