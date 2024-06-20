#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <mutex>
#include <thread>
#include <condition_variable>

#include "../Base/BaseObject.hpp"

#ifndef SQUARE_HPP
#define SQUARE_HPP

class Square : public BaseObject {
private:
	int corner;
	GLfloat mainSpeed;
	GLfloat eleSpeed;
	bool isElevating;
	bool canElevate;
	std::condition_variable cv;
	std::mutex carMtx;

public:
	int rounds;

	Square();
	Square(GLfloat startX, GLfloat startY, GLfloat squareSize, GLfloat squareSpeed, GLfloat elevatingSpeed, GLfloat r, GLfloat g, GLfloat b);
	void move();
	void checkAndElevate(bool elevatorTopStatus, bool elevatorRunningStatus);
};

#endif
