#include "Square.hpp"

Square::Square() { }

Square::Square(GLfloat startX, GLfloat startY, GLfloat squareSize, GLfloat squareSpeed, GLfloat elevatingSpeed, GLfloat r, GLfloat g, GLfloat b)
	: BaseObject(startX, startY, squareSize, squareSpeed, r, g, b), corner(0), mainSpeed(squareSpeed), eleSpeed(elevatingSpeed), isElevating(false), canElevate(false), rounds(0) { }

void Square::move() {
	if (isElevating) {
		speed = eleSpeed;
	} else {
		speed = mainSpeed;
	}

	switch (corner) {
		case 0:
			x += speed;
			if (x >= 0.5f) {
				x = 0.5f;
				corner = 1;
			}
			break;
		case 1:
			if (canElevate) {
				isElevating = true;
				y -= speed;
				if (y <= -0.5f) {
					y = -0.5f;
					canElevate = false;
					isElevating = false;
					corner = 2;
				}
			}
			break;
		case 2:
			x -= speed;
			if (x <= -0.5f) {
				x = -0.5f;
				corner = 3;
			}
			break;
		case 3:
			y += speed;
			if (y >= 0.5f) {
				y = 0.5f;
				corner = 1;
				rounds++;
				corner = 0;
			}
			break;
	}
}

void Square::checkAndElevate(bool elevatorTopStatus, bool elevatorRunningStatus) {
	if (corner == 1 && elevatorTopStatus && !elevatorRunningStatus) {
		canElevate = true;
	}
}
