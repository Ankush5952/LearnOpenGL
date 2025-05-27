#pragma once

#include"Includes.h"

const unsigned int width = 1600; //Window Width
const unsigned int height = 900; //Window Height

glm::mat4 model;
glm::mat4 view;
glm::mat4 proj;

Camera cam;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float lastX = width / 2;
float lastY = height / 2;
bool firstMouse = true;

//float Kc = 1.0f;
//float Kl = 0.09f;
//float Kq = 0.032f;

void framebuffer_size_callback(GLFWwindow* window, int w, int h) //Buffer callback function for window resize
{
	glViewport(0, 0, w, h);
}

void cursor_callback(GLFWwindow* window, double xPos, double yPos)
{
	//1.calculate mouse offset since last frame
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xoffset = xPos - lastX;
	float yoffset = yPos - lastY;
	lastX = xPos;
	lastY = yPos;

	cam.ProcessMouseMovement(xoffset, yoffset);

}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
	cam.ProcessScroll(yOffset);
}

void ProcessInput(GLFWwindow* window) //Input Manager
{
	//Movement
	if (glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS)
	{
		cam.ProcessKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS)
	{
		cam.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
	{
		cam.ProcessKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS)
	{
		cam.ProcessKeyboard(RIGHT, deltaTime);
	}

	//Exit
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
