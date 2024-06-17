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
	// Create threads to manage elements
	std::thread elevatorThread = std::thread(&Simulation::manageElevatorThread, this, elevator, std::ref(stopThreads));

	for (size_t i = 0; i < squares.size(); i++) {
		allThreads.emplace_back(&Simulation::manageSquareThread, this, squares[i], elevator, std::ref(stopThreads));
	}

	// Main drawing/events loop
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		Board::drawTrack();

		for (size_t i = 0; i < squares.size(); i++) {
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

	// Close threads
	stopAllThreads(elevatorThread);

	// Clear memory
	clearAllElements();

	// Close window
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Simulation::createElements() {
	elevator = new Elevator(0.5f, 0.5f, 0.1f, elevatingSpeed, elevatingSpeed, 1.0f, 1.0f, 1.0f);

	for (int i = 0; i < elementsCount; i++) {
		squares.push_back(createSquare());
	}
}

Square* Simulation::createSquare() {
	std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> colorDist(0.0f, 1.0f);
	std::uniform_real_distribution<float> speedDist(0.0004f, 0.0008f);

	GLfloat red = colorDist(gen);
	GLfloat green = colorDist(gen);
	GLfloat blue = colorDist(gen);

	return new Square(-0.5f, 0.5f, 0.1f, speedDist(gen), elevatingSpeed, red, green, blue);
}

void Simulation::manageSquareThread(Square *s, Elevator *e, bool &stopThreadStatus) {
	while (true) {
		if (s == nullptr) {
			return;
		}

		if (stopThreadStatus || s->rounds == maxRounds) {
			auto it = std::find(squares.begin(), squares.end(), s);
			if (it != squares.end()) {
					squares.erase(it);
			}

			delete s;

			// Create new square object and thread for it
			Square *newSquare = createSquare();
			squares.push_back(newSquare);
			allThreads.emplace_back(&Simulation::manageSquareThread, this, newSquare, elevator, std::ref(stopThreads));
			return;
		}

		s->checkAndElevate(e->getTop(), e->getRunning());
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

void Simulation::stopAllThreads(std::thread &elevatorThread) {
	stopThreads = true;
	for (auto& thread : allThreads) {
		if (thread.joinable()) {
			thread.join();
		}
	}

	if (elevatorThread.joinable()) {
    elevatorThread.join();
  }
}

void Simulation::clearAllElements() {
	{
		std::lock_guard<std::mutex> lock(mtx);
		for (auto& square : squares) {
				delete square;
		}

		delete elevator;
  }

	squares.clear();
	allThreads.clear();
}
