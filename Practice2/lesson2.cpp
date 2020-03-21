#include <iostream>
#include <sstream>
//#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
using namespace std;

const char* TITLE = "Introduction - Triangle";
const int gWindowWidth = 800;
const int gWindowHeight = 600;
bool initOpenGL();
GLFWwindow* gWindow = NULL;
bool gWireFrame = false;

const GLchar* vertexShaderSrc =
"#version 330 core\n"
"layout (location = 0) in vec3 pos;"
"void main()"
"{"
"	gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);"
"}";

const GLchar* fragmentShaderSrc =
"#version 330 core\n"
"out vec4 frag_color;"
"void main()"
"{"
"	frag_color = vec4(0.35f, 0.96f, 0.3f, 1.0f);"
"}";

void glfw_onkey(GLFWwindow* window, int key, int scancode, int action, int mode);
void showFPS(GLFWwindow* window);

int main() {
	if (!initOpenGL()) {
		cerr << "GLFW Initialization failed!" << endl;
		return false;
	}

	GLfloat vertices[] = {
		// Tri 0			
		-0.5f,	0.5f,	0.0f,	// Top
		 0.5f,	0.5f,	0.0f,	// Left
		 0.5f,	-0.5f,	0.0f,	// Right

		 // Tri 1
		-0.5f,	0.5f,	0.0f,	// Top
		-0.5f,	-0.5f,	0.0f,	// Left
		 0.5f,	-0.5f,	0.0f,	// Right
	};

	GLfloat vert_color[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	GLuint vao, vbo;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertexShaderSrc, NULL);
	glCompileShader(vs);

	GLint result;
	GLchar infolog[512];
	glGetShaderiv(vs, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(vs, sizeof(infolog), NULL, infolog);
		cout << "Error! Vertex shader failed to compile. " << infolog << endl;
	}

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(fs, sizeof(infolog), NULL, infolog);
		cout << "Error! Fragment shader failed to compile. " << infolog << endl;
	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vs);
	glAttachShader(shaderProgram, fs);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderProgram, sizeof(infolog), NULL, infolog);
		cout << "Error! Shader program linker failure." << infolog << endl;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);

	// Main loop
	while (!glfwWindowShouldClose(gWindow)) {
		showFPS(gWindow);
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		glfwSwapBuffers(gWindow);
	}

	glDeleteProgram(shaderProgram);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

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