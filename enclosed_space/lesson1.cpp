#include <iostream>

//#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
using namespace std;

const char* TITLE = "Introduction";
const int gWindowWidth = 800;
const int gWindowHeight = 600;

//void glfw_onkey(GLFWwindow* window, int key, int scancode, int action, int mode);

int main() {
	if (!glfwInit()) {
		cerr << "GLFW initialization failed!" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* pWindow = glfwCreateWindow(gWindowWidth, gWindowHeight, TITLE, NULL, NULL);

	if (pWindow == NULL) {
		cerr << "Failed to create GLFW Window" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(pWindow);

	//glfwSetKeyCallback(pWindow, glfw_onkey);

	glewExperimental = GL_TRUE;

	// Main loop
	while (!glfwWindowShouldClose(pWindow)) {
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

//void glfw_onkey(GLFWwindow* window, int key, int scancode, int action, int mode) {
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
//		glfwSetWindowShouldClose(window, GL_TRUE);
//	}
//}