#include "InputHandler.hpp"

InputHandler::InputHandler(sf::RenderWindow& win, int pSize) 
	: window(win), pixelSize(pSize) {}

void InputHandler::update() {
	handleKeyboardInput();
}

bool InputHandler::getParticlePlacement(int& outGridX, int& outGridY, ParticleType& outType) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);

		outGridX = mousePos.x / pixelSize;
		outGridY = mousePos.y / pixelSize;
		outType = currentParticleType;

		return true;
	}
	return false;
}

ParticleType InputHandler::getCurrentParticleType() const {
	return currentParticleType;
}

void InputHandler::handleKeyboardInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
		currentParticleType = ParticleType::Sand;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
		currentParticleType = ParticleType::Water;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
		currentParticleType = ParticleType::Snow;
	}

	// Check if spacebar is just pressed
	static bool wasSpacePressed = false;
	bool isSpacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	clearPressed = isSpacePressed && !wasSpacePressed;
	wasSpacePressed = isSpacePressed;
}

bool InputHandler::shouldClearGrid() const {
	return clearPressed;
}