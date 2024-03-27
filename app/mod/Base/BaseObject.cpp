#include "BaseObject.hpp"

BaseObject::BaseObject() { }

BaseObject::BaseObject(GLfloat startX, GLfloat startY, GLfloat size, GLfloat speed, GLfloat r, GLfloat g, GLfloat b)
	: x(startX), y(startY), size(size), speed(speed) {
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

GLfloat BaseObject::getX() {
	return x;
}

GLfloat BaseObject::getY() {
	return y;
}

void BaseObject::draw() {
	glPushMatrix();
	glColor3fv(color);
	glTranslatef(x, y, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(-size / 2, -size / 2);
	glVertex2f(size / 2, -size / 2);
	glVertex2f(size / 2, size / 2);
	glVertex2f(-size / 2, size / 2);
	glEnd();
	glPopMatrix();
}
