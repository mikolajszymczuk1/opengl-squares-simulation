#include "Simulation.hpp"

Simulation::Simulation(GLint windowWidth, GLint windowHeight) : width(windowWidth), height(windowHeight) { }

int Simulation::init() {
	if (!glfwInit()) {
		printf("GLFW Initialization failed\n");
		return 1;
	}

	window = glfwCreateWindow(width, height, "Open GL Squares Simulation", NULL, NULL);

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

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	return 0;
}

void Simulation::simulationLoop() {
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		Board::drawTrack();

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
}

void Simulation::createElements() {
	e1 = Elevator(0.5f, 0.5f, 0.1f, 0.01f, 0.02f, 1.0f, 1.0f, 1.0f);
	s1 = Square(-0.5f, 0.5f, 0.1f, 0.008f, 1.0f, 0.0f, 0.0f);

	e2 = Elevator(0.5f, 0.5f, 0.1f, 0.01f, 0.02f, 1.0f, 1.0f, 1.0f);
	s2 = Square(-0.5f, 0.5f, 0.1f, 0.005f, 0.0f, 1.0f, 0.0f);

	elevators = new Elevator[2] { e1, e2 };
	squares = new Square[2] { s1, s2 };
}
