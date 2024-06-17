#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <mutex>
#include <random>
#include <vector>
#include <algorithm>

#include "../Board/Board.hpp"
#include "../Elevator/Elevator.hpp"
#include "../Square/Square.hpp"

#ifndef SIMULATION_HPP
#define SIMULATION_HPP

class Simulation {
private:
	GLint width;
	GLint height;
	GLFWwindow *window;

	std::mutex mtx;

	Elevator *elevator;
	std::vector<Square*> squares;
	std::vector<std::thread> allThreads;
	GLfloat elevatingSpeed = 0.0008f;

	int elementsCount = 5;
	int maxRounds = 4;
	bool stopThreads = false;

public:
	Simulation(GLint windowWidth, GLint windowHeight);
	int init();
	void simulationLoop();
	void createElements();
	Square* createSquare();
	void manageSquareThread(Square *s, Elevator *e, bool &stopThreadStatus);
	void manageElevatorThread(Elevator *e, bool &stopThreadStatus);
	void stopAllThreads(std::thread &elevatorThread);
	void clearAllElements();
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif
