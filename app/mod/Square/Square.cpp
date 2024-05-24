#include "Square.hpp"

Square::Square() { }

Square::Square(GLfloat startX, GLfloat startY, GLfloat squareSize, GLfloat squareSpeed, GLfloat r, GLfloat g, GLfloat b)
	: BaseObject(startX, startY, squareSize, squareSpeed, r, g, b), corner(1), mainSpeed(squareSpeed), isElevating(false), rounds(0) { }

void Square::move() {
	if (isElevating) {
		speed = 0.001f;
	} else {
		speed = mainSpeed;
	}

	switch (corner) {
		case 1:
			x += speed;
			if (x >= 0.5f) {
				x = 0.5f;
				isElevating = true;
				corner = 2;
			}
			break;
		case 2:
			y -= speed;
			if (y <= -0.5f) {
				y = -0.5f;
				isElevating = false;
				corner = 3;
			}
			break;
		case 3:
			x -= speed;
			if (x <= -0.5f) {
				x = -0.5f;
				corner = 0;
			}
			break;
		case 0:
			y += speed;
			if (y >= 0.5f) {
				y = 0.5f;
				corner = 1;
				rounds++;
			}
			break;
	}
}
