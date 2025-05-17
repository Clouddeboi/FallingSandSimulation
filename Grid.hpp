#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Particle.hpp"

using namespace std;

class Grid{
public:
	//Constructor
	Grid(int width, int height, int particleSize);

	//Draw all particles to the window
	void draw(sf::RenderWindow& window);

private:
	int width, height;//Grid size (in particles)
	int particleSize;//Size of each particle(square in pixels)

	vector<vector<Particle>> particles;//2D Grid of particles
};