/*
Usage: This function resizes window as desired
Where to put: after Glinit();
*/
void framebuffer_resize_callback(GLFWindow* window, int fbW, int fbH){
	glViewport(0, 0, fbW fbH);
}

/*
Usage: This function does something when escape key is pressed
Where to put: in main loop;
*/
void updateInput(GLFWindow* window){
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		// Close the window
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) // Unfilled polygon
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) // Filled polygon
glEnable(GL_BLEND) // Colors are blended
