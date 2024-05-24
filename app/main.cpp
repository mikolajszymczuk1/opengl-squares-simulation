#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "mod/Simulation/Simulation.hpp"

int main() {
	Simulation *simulation = new Simulation(600, 600);
	simulation->init();
	simulation->createElements();
	simulation->simulationLoop();
	return 0;
}
