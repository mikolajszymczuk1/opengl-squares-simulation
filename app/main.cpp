#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const GLint WIDTH = 600;
const GLint HEIGHT = 600;

class BaseObject {
protected:
	GLfloat x, y;
	GLfloat size;
	GLfloat speed;
	GLfloat color[3];

public:
	BaseObject(GLfloat startX, GLfloat startY, GLfloat size, GLfloat speed, GLfloat r, GLfloat g, GLfloat b)
		: x(startX), y(startY), size(size), speed(speed) {
		color[0] = r;
		color[1] = g;
		color[2] = b;
	}

	GLfloat getX() {
		return x;
	}

	GLfloat getY() {
		return y;
	}

	void draw() {
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
};

class Elevator : public BaseObject {
private:
	bool isRunning;
	GLfloat speedUp;

public:
	Elevator(GLfloat startX, GLfloat startY, GLfloat elevatorSize, GLfloat elevatorSpeedDown, GLfloat elevatorSpeedUp, GLfloat r, GLfloat g, GLfloat b)
		: BaseObject(startX, startY, elevatorSize, elevatorSpeedDown, r, g, b), isRunning(false), speedUp(elevatorSpeedUp) { }

	void run() {
		isRunning = true;
	}

	void move() {
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
};

class Square : public BaseObject {
private:
	int corner;
	GLfloat mainSpeed;
	bool isElevating;

public:
	Square(GLfloat startX, GLfloat startY, GLfloat squareSize, GLfloat squareSpeed, GLfloat r, GLfloat g, GLfloat b)
		: BaseObject(startX, startY, squareSize, squareSpeed, r, g, b), corner(1), mainSpeed(squareSpeed), isElevating(false) { }

	void move() {
		if (isElevating) {
			speed = 0.0001f;
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
				}
				break;
		}
	}
};

void drawTrack() {
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

void initializeOpenGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main() {
	if (!glfwInit()) {
		printf("GLFW Initialization failed\n");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Open GL Squares Simulation", NULL, NULL);
	if (!window) {
		printf("GLFW window creation failed\n");
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		printf("GLEW initialization failed\n");
		glfwDestroyWindow(window);
		glfwTerminate();
		return 1;
	}

	initializeOpenGL();

	Elevator e1 = Elevator(0.5f, 0.5f, 0.1f, 0.0001f, 0.001f, 1.0f, 1.0f, 1.0f);
	Square s1 = Square(-0.5f, 0.5f, 0.1f, 0.0003f, 1.0f, 0.0f, 0.0f);

	Elevator e2 = Elevator(0.5f, 0.5f, 0.1f, 0.0001f, 0.001f, 1.0f, 1.0f, 1.0f);
	Square s2 = Square(-0.5f, 0.5f, 0.1f, 0.00018f, 0.0f, 1.0f, 0.0f);

	Elevator elevators[] = { e1 };
	Square squares[] = { s1 };

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		drawTrack();

		/**
		for (int i = 0; i < sizeof(squares) / sizeof(squares[0]); ++i) {
			squares[i].move();
			squares[i].draw();
		}

		for (int i = 0; i < sizeof(elevators) / sizeof(elevators[0]); ++i) {
			elevators[i].move();
			elevators[i].draw();
		}
		*/

		s1.move();
		e1.move();
		s2.move();
		e2.move();

		if (s1.getX() >= e1.getX() && s1.getY() <= e1.getY()) {
			e1.run();
		}

		if (s2.getX() >= e2.getX() && s2.getY() <= e2.getY()) {
			e2.run();
		}

		s1.draw();
		e1.draw();
		s2.draw();
		e2.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
