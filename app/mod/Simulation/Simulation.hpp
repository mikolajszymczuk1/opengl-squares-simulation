#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <mutex>
#include <random>

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
	Square *squares[5];
	int elementsArraySize = 5;
	int maxRounds = 4;
	GLfloat elevatingSpeed = 0.0008f;

	bool stopThreads;

public:
	Simulation(GLint windowWidth, GLint windowHeight);
	int init();
	void simulationLoop();
	void createElements();
	void manageSquareThread(Square *s, Elevator *e, bool &stopThreadStatus);
	void manageElevatorThread(Elevator *e, bool &stopThreadStatus);
};

#endif
