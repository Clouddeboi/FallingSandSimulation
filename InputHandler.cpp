#include "InputHandler.hpp"

InputHandler::InputHandler(sf::RenderWindow& win, int pSize) 
	: window(win), pixelSize(pSize) {}

bool InputHandler::getSandPlacement(int& outGridX, int& outGridY) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);

		outGridX = mousePos.x / pixelSize;
		outGridY = mousePos.y / pixelSize;

		return true;
	}
	return false;
}