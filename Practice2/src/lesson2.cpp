#include <iostream>
#include <sstream>
//#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "ShaderProgram.h"

using namespace std;

const char* TITLE = "Shader";
const int gWindowWidth = 800;
const int gWindowHeight = 600;
bool initOpenGL();
GLFWwindow* gWindow = NULL;
bool gWireFrame = false;


void glfw_onkey(GLFWwindow* window, int key, int scancode, int action, int mode);
void showFPS(GLFWwindow* window);

int main() {
	if (!initOpenGL()) {
		cerr << "GLFW Initialization failed!" << endl;
		return false;
	}

	GLfloat vertices[] = {
		// Tri 0			
		-0.5f,	0.5f,	0.0f,	
		 0.5f,	0.5f,	0.0f,	
		 0.5f,	-0.5f,	0.0f,
		-0.5f,	-0.5f,	0.0f
		 
	};

	GLuint indices[] = {
		0, 1, 2,	// Tri 0
		0, 2, 3		// Tri 1
	};

	GLuint vao, ibo, vbo;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	ShaderProgram shaderProgram;
	shaderProgram.loadShaders("shaders/basic.vert", "shaders/basic.frag");

	// Main loop
	while (!glfwWindowShouldClose(gWindow)) {
		showFPS(gWindow);
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.use();

		GLfloat time = glfwGetTime();
		GLfloat blueColor = (sin(time) / 2) + 0.5f;
		glm::vec2 pos;
		pos.x = sin(time) / 2;
		pos.y = cos(time) / 2;
		shaderProgram.setUniform("posOffset", pos);
		shaderProgram.setUniform("vertColor", glm::vec4(0.0f, 0.0f, blueColor, 1.0f));

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(gWindow);
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);

	glfwTerminate();

	return 0;
}

void glfw_onkey(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		gWireFrame = !gWireFrame;
		if (gWireFrame) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

bool initOpenGL() {
	if (!glfwInit()) {
		cerr << "GLFW initialization failed!" << endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	gWindow = glfwCreateWindow(gWindowWidth, gWindowHeight, TITLE, NULL, NULL);

	if (gWindow == NULL) {
		cerr << "Failed to create GLFW Window" << endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(gWindow);

	glfwSetKeyCallback(gWindow, glfw_onkey);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		cerr << "Glew initialization failed!" << endl;
		return false;
	}

	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
	return true;
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