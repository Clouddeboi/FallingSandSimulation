#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Particle.hpp"

using namespace std;

class Grid{
public:
	//Constructor
	Grid(int width, int height, int particleSize);

	//Method that will update every frame
	void update();

	//Draw all particles to the window
	void draw(sf::RenderWindow& window);
	//Set a particle at grid Coords
	void setParticle(int x, int y, ParticleType type);

	//Getter for the particle size, 
	//this is so we can easily assign the particle size inside of the input handler
	int getParticleSize() const;

private:
	int width, height;//Grid size (in particles)
	int particleSize;//Size of each particle(square in pixels)

	vector<vector<Particle>> particles;//2D Grid of particles

	//More particles!
	//All particles will have their own behaviours
	void updateSnow(int x, int y);
	void updateSand(int x, int y);
};