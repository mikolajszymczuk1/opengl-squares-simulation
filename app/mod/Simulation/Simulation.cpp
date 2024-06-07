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
	stopThreads = false;

	// Create threads to manage elements
	std::thread allThreads[elementsArraySize];
	for (int i = 0; i < elementsArraySize; i++) {
		allThreads[i] = std::thread(&Simulation::updateSquareAndElevatorThread, this, std::ref(squares[i]), std::ref(elevators[i]), std::ref(stopThreads));
	}

	// Main drawing/events loop
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		Board::drawTrack();

		for (int i = 0; i < elementsArraySize; i++) {
			if (squares[i] != nullptr) {
				squares[i]->draw();
			}

			if (elevators[i] != nullptr) {
				elevators[i]->draw();
			}
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Stop all threads
	stopThreads = true;
	for (int i = 0; i < elementsArraySize; i++) {
		allThreads[i].join();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}

void Simulation::createElements() {
	for (int i = 0; i < elementsArraySize; i++) {
		elevators[i] = new Elevator(0.5f, 0.5f, 0.1f, 0.001f, 0.002f, 1.0f, 1.0f, 1.0f);
		squares[i] = new Square(-0.5f, 0.5f, 0.1f, 0.0002f * (i + 1), 0.6f, 0.2f, 1.0f);
	}
}

void Simulation::updateSquareAndElevatorThread(Square *s, Elevator *e, bool &stopThreadStatus) {
	while (true) {
		if (s == nullptr) {
			return;
		}

		if (e == nullptr) {
			return;
		}

		if (stopThreadStatus || s->rounds == maxRounds) {
			delete s;
			delete e;
			return;
		}

		s->move();
		e->move();

		if (s->getX() >= e->getX() && s->getY() <= e->getY()) {
			e->run();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}
