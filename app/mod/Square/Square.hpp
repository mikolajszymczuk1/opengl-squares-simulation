#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Base/BaseObject.hpp"

#ifndef SQUARE_HPP
#define SQUARE_HPP

class Square : public BaseObject {
private:
	int corner;
	GLfloat mainSpeed;
	bool isElevating;

public:
	int rounds;

	Square();
	Square(GLfloat startX, GLfloat startY, GLfloat squareSize, GLfloat squareSpeed, GLfloat r, GLfloat g, GLfloat b);
	void move();
};

#endif
