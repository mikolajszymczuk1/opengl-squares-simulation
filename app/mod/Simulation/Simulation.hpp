#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
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

	Elevator *elevators;
	Square *squares;

	Elevator e1, e2;
	Square s1, s2;

public:
	Simulation(GLint windowWidth, GLint windowHeight);
	int init();
	void simulationLoop();
	void createElements();
};

#endif
