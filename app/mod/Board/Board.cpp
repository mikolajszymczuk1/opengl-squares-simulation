#include "Board.hpp"

void Board::drawTrack() {
	glColor3f(0.1f, 0.1f, 0.1f);
	glBegin(GL_QUADS);
	glVertex2f(-0.55f, -0.55f);
	glVertex2f(0.55f, -0.55f);
	glVertex2f(0.55f, 0.55f);
	glVertex2f(-0.55f, 0.55f);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(-0.45f, -0.45f);
	glVertex2f(0.55f, -0.45f);
	glVertex2f(0.55f, 0.45f);
	glVertex2f(-0.45f, 0.45f);
	glEnd();
}
