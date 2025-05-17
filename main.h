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
glm::vec3 camUp;
glm::vec3 camFront;

float deltaTime = 0.0f;
float lastFrame = 0.0f;


void framebuffer_size_callback(GLFWwindow* window, int w, int h) //Buffer callback function for window resize
{
	glViewport(0, 0, w, h);
}

void ProcessInput(GLFWwindow* window) //Input Manager
{
	const float camSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS)
	{
		camPos += camSpeed * camFront; //move in front dir
	}
	if (glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS)
	{
		camPos -= camSpeed * camFront; //move in front dir
	}
	if (glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
	{
		camPos -= camSpeed * glm::normalize(glm::cross(camFront,camUp)); //move in front dir
	}
	if (glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS)
	{
		camPos += camSpeed * glm::normalize(glm::cross(camFront, camUp));
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}