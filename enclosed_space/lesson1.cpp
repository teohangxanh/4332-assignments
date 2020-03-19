#include <iostream>
#include <sstream>
//#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
using namespace std;

const char* TITLE = "Introduction";
const int gWindowWidth = 800;
const int gWindowHeight = 600;
bool gFullScreen = false;

void glfw_onkey(GLFWwindow* window, int key, int scancode, int action, int mode);
void showFPS(GLFWwindow* window);

int main() {
	if (!glfwInit()) {
		cerr << "GLFW initialization failed!" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* pWindow = NULL;
	if (gFullScreen) {
		GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* pvmode = glfwGetVideoMode(pMonitor);
		if (pvmode != NULL) {
			pWindow = glfwCreateWindow(pvmode->width, pvmode->height, TITLE, pMonitor, NULL);
		}
	}
	else {
		pWindow = glfwCreateWindow(gWindowWidth, gWindowHeight, TITLE, NULL, NULL);
	}

	if (pWindow == NULL) {
		cerr << "Failed to create GLFW Window" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(pWindow);

	glfwSetKeyCallback(pWindow, glfw_onkey);

	glewExperimental = GL_TRUE;

	// Main loop
	while (!glfwWindowShouldClose(pWindow)) {
		showFPS(pWindow);
		glfwPollEvents();
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(pWindow);
	}

	
	if (glewInit() != GLEW_OK) {
		cerr << "Glew initialization failed!" << endl;
	}
	glfwTerminate();
	return 0;
}

void glfw_onkey(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void showFPS(GLFWwindow* window) {
	static double previousSeconds = 0.0;
	static int frameCount = 0;
	double elapsedSeconds;
	double currentSeconds = glfwGetTime(); // returns number of seconds sicen GLFW started, as a double
	elapsedSeconds = currentSeconds - previousSeconds;

	// limit text update 4 times per second
	if (elapsedSeconds > 0.25) {
		previousSeconds = currentSeconds;
		double fps = (double)frameCount / elapsedSeconds;
		double msPerFrame = 1000.0 / fps;
		ostringstream outs;
		outs.precision(3);
		outs << fixed
			<< TITLE << "     "
			<< "FPS: " << fps << "     "
			<< "Frame time: " << msPerFrame << " (ms)";
		glfwSetWindowTitle(window, outs.str().c_str());

		frameCount = 0;
	}
	frameCount++;
}