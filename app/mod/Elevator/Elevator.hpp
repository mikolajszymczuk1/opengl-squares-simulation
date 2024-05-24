#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Base/BaseObject.hpp"

#ifndef ELEVATOR_HPP
#define ELEVATOR_HPP

class Elevator : public BaseObject {
private:
	bool isRunning;
	GLfloat speedUp;

public:
	Elevator();
	Elevator(GLfloat startX, GLfloat startY, GLfloat elevatorSize, GLfloat elevatorSpeedDown, GLfloat elevatorSpeedUp, GLfloat r, GLfloat g, GLfloat b);
	void run();
	void move();
};

#endif
