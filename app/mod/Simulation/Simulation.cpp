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
	std::thread elevatorThread = std::thread(&Simulation::manageElevatorThread, this, std::ref(elevator), std::ref(stopThreads));

	std::thread allThreads[elementsArraySize];
	for (int i = 0; i < elementsArraySize; i++) {
		allThreads[i] = std::thread(&Simulation::manageSquareThread, this, std::ref(squares[i]), std::ref(elevator), std::ref(stopThreads));
	}

	// Main drawing/events loop
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		Board::drawTrack();

		for (int i = 0; i < elementsArraySize; i++) {
			if (squares[i] != nullptr) {
				squares[i]->draw();
			}
		}

		if (elevator != nullptr) {
			elevator->draw();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Stop all threads
	stopThreads = true;
	for (int i = 0; i < elementsArraySize; i++) {
		allThreads[i].join();
	}

	elevatorThread.join();

	glfwDestroyWindow(window);
	glfwTerminate();
}

void Simulation::createElements() {
	std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dist(0.0f, 1.0f);

	elevator = new Elevator(0.5f, 0.5f, 0.1f, elevatingSpeed, elevatingSpeed, 1.0f, 1.0f, 1.0f);

	for (int i = 0; i < elementsArraySize; i++) {
		GLfloat red = dist(gen);
		GLfloat green = dist(gen);
		GLfloat blue = dist(gen);

		squares[i] = new Square(-0.5f, 0.5f, 0.1f, 0.0002f * (i + 1), elevatingSpeed, red, green, blue);
	}
}

void Simulation::manageSquareThread(Square *s, Elevator *e, bool &stopThreadStatus) {
	while (true) {
		if (s == nullptr) {
			return;
		}

		if (stopThreadStatus || s->rounds == maxRounds) {
			delete s;
			return;
		}

		mtx.lock();
		s->checkAndElevate(e->getTop(), e->getRunning());
		mtx.unlock();

		s->move();

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void Simulation::manageElevatorThread(Elevator *e, bool &stopThreadStatus) {
	while (true) {
		if (stopThreadStatus) {
			delete e;
			return;
		}

		if (e->getTop()) {
			e->run();
		}

		e->move();

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}
