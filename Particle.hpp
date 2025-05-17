#pragma once
#include <SFML/Graphics.hpp>

//Defining the particles for the simulation
enum class ParticleType {
	Empty, //Empty Particle
	Sand, //Sand Particle
	Water, //Water Particle
	Snow, //Snow Particle
};

//This Represents a single particle in the grid
struct Particle {
	//Default (empty)
	ParticleType type = ParticleType::Empty;
	//Default colour for the empty is black
	sf::Color color = sf::Color::Black;
};