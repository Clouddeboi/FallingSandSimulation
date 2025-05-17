#pragma once
#include <SFML/Graphics.hpp>
#include "Particle.hpp"

class InputHandler {
public:
	InputHandler(sf::RenderWindow& window, int particleSize);

	//Returns true if a particle should be placed on this frame
	//outputs the grid coords to place it on
	bool getParticlePlacement(int& outGridX, int& outGridY, ParticleType& outType);

	ParticleType getCurrentParticleType() const;

	void update();

private:
	sf::RenderWindow& window;
	int pixelSize;

	ParticleType currentParticleType = ParticleType::Sand;

	void handleKeyboardInput();
};