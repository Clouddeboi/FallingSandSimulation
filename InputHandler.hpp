#pragma once
#include <SFML/Graphics.hpp>

class InputHandler {
public:
	InputHandler(sf::RenderWindow& window, int particleSize);

	//Returns true if a particle should be placed on this frame
	//outputs the grid coords to place it on
	bool getSandPlacement(int& outGridX, int& outGridY);

private:
	sf::RenderWindow& window;
	int pixelSize;
};