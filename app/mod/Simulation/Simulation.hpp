#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <mutex>

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

	Elevator *elevators[5];
	Square *squares[5];
	int elementsArraySize = 5;
	int maxRounds = 2;

	bool stopThreads;

public:
	Simulation(GLint windowWidth, GLint windowHeight);
	int init();
	void simulationLoop();
	void createElements();
	void updateSquareAndElevatorThread(Square *s, Elevator *e, bool &stopThreadStatus);
};

#endif
