#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#ifndef BASEOBJECT_HPP
#define BASEOBJECT_HPP

class BaseObject {
protected:
	GLfloat x, y;
	GLfloat size;
	GLfloat speed;
	GLfloat color[3];

public:
	BaseObject();
	BaseObject(GLfloat startX, GLfloat startY, GLfloat size, GLfloat speed, GLfloat r, GLfloat g, GLfloat b);
	GLfloat getX();
	GLfloat getY();
	void draw();
};

#endif
