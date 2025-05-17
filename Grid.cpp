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

//Update Method
void Grid::update() {
    for (int y = height - 2; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            Particle& p = particles[y][x];

            switch (p.type) {
            case ParticleType::Snow:
                updateSnow(x, y);
                break;
            case ParticleType::Sand:
                updateSand(x, y);
                break;
            case ParticleType::Water:
                updateWater(x, y);
                break;
            default:
                break;
            }
        }
    }
}

void Grid::updateSnow(int x, int y) {
    Particle& p = particles[y][x];
    //Collect candidate positions to move into
    vector<pair<int, int>> candidates;

    for (int dy = 1; dy <= 1; ++dy) { //Only one row below
        for (int dx = -1; dx <= 1; ++dx) {
            int nx = x + dx;
            int ny = y + dy;

            //Check bounds
            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                if (particles[ny][nx].type == ParticleType::Empty) {
                    candidates.emplace_back(nx, ny);
                }
            }
        }
    }

    if (!candidates.empty()) {
        //Pick a random candidate if available and move into for natural spreading
        auto& pos = candidates[rand() % candidates.size()];
        particles[pos.second][pos.first] = p;
        p.type = ParticleType::Empty;
        p.color = sf::Color::Black;
    }
}

void Grid::updateSand(int x, int y) {
    if (y + 1 >= height) return; //Out of bounds check

    Particle& p = particles[y][x];
    Particle& below = particles[y + 1][x];

    if (below.type == ParticleType::Empty) {
        below = p;
        p = Particle(); //Reset to empty
    }
    else if (below.type == ParticleType::Water) {
        // Swap sand and water
        swap(p, below);
    }
    else {
        //Try diagonal movement
        if (x > 0 && y + 1 < height && particles[y + 1][x - 1].type == ParticleType::Empty) {
            particles[y + 1][x - 1] = p;
            p = Particle();
        }
        else if (x < width - 1 && y + 1 < height && particles[y + 1][x + 1].type == ParticleType::Empty) {
            particles[y + 1][x + 1] = p;
            p = Particle();
        }
    }
}

void Grid::updateWater(int x, int y) {
    Particle& p = particles[y][x];

    //Check directly below
    if (y + 1 < height && particles[y + 1][x].type == ParticleType::Empty) {
        particles[y + 1][x] = p;
        p = Particle(); //Set current to empty
        return;
    }

    //Check bottom-left
    if (x > 0 && y + 1 < height && particles[y + 1][x - 1].type == ParticleType::Empty) {
        particles[y + 1][x - 1] = p;
        p = Particle();
        return;
    }

    //Check bottom-right
    if (x < width - 1 && y + 1 < height && particles[y + 1][x + 1].type == ParticleType::Empty) {
        particles[y + 1][x + 1] = p;
        p = Particle();
        return;
    }

    //Check left
    if (x > 0 && particles[y][x - 1].type == ParticleType::Empty) {
        particles[y][x - 1] = p;
        p = Particle();
        return;
    }

    //Check right
    if (x < width - 1 && particles[y][x + 1].type == ParticleType::Empty) {
        particles[y][x + 1] = p;
        p = Particle();
        return;
    }
}

ParticleType Grid::getParticleType(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height)
        return ParticleType::Empty; //Treat out of bounds as an empty
    return particles[y][x].type;
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
    if (x < 0 || x >= width || y < 0 || y >= height)
        return;

    particles[y][x].type = type;

    switch (type) {
    case ParticleType::Sand:
        particles[y][x].color = sf::Color(194, 178, 128);
        break;
    case ParticleType::Water:
        particles[y][x].color = sf::Color(64, 164, 223); 
        break;
    case ParticleType::Snow:
        particles[y][x].color = sf::Color(255, 255, 255);
        break;
    default:
        particles[y][x].color = sf::Color::Black; //Empty 
        break;
    }
}

