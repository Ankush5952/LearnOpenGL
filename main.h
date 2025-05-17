#pragma once

unsigned int VAO;
unsigned int VBO;

unsigned int texture1;
unsigned int texture2;

glm::mat4 trans;

glm::mat4 model;
glm::mat4 view;
glm::mat4 proj;

glm::vec3 camPos;
glm::vec3 camTarget;
glm::vec3 camDir;
glm::vec3 camUp;
glm::vec3 camRight;
glm::vec3 up;
glm::vec3 camFront;


void framebuffer_size_callback(GLFWwindow* window, int w, int h) //Buffer callback function for window resize
{
	glViewport(0, 0, w, h);
}

void ProcessInput(GLFWwindow* window) //Input Manager
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}