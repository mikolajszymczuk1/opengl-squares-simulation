#include "Elevator.hpp"

Elevator::Elevator() { }

Elevator::Elevator(GLfloat startX, GLfloat startY, GLfloat elevatorSize, GLfloat elevatorSpeedDown, GLfloat elevatorSpeedUp, GLfloat r, GLfloat g, GLfloat b)
	: BaseObject(startX, startY, elevatorSize, elevatorSpeedDown, r, g, b), isRunning(false), speedUp(elevatorSpeedUp) { }

void Elevator::run() {
	isRunning = true;
}

void Elevator::move() {
	if (!isRunning) {
		y += speedUp;
		if (y >= 0.5f) {
			y = 0.5f;
		}
	} else {
		y -= speed;
		if (y <= -0.5f) {
			y = -0.5f;
			isRunning = false;
		}
	}
}
