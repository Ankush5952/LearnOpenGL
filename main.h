#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <iostream>
#include<stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

const unsigned int width = 1600; //Window Width
const unsigned int height = 900; //Window Height

unsigned int VAO;
unsigned int VBO;

unsigned int texture1;
unsigned int texture2;

glm::mat4 trans;

float fov;

glm::mat4 model;
glm::mat4 view;
glm::mat4 proj;

glm::vec3 camPos;
glm::vec3 camUp;
glm::vec3 camFront;
glm::vec3 camDir;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float yaw = -90.0f;
float pitch = 0.0f;

float lastX = width / 2;
float lastY = height / 2;
bool firstMouse = true;

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

	//set some sensitivity to the mouse movement
	const float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	//2. add offset to yaw and pitch
	yaw += xoffset;
	pitch += yoffset;

	//3.add constraints to pitch
	if (pitch > 89.0f) { pitch = 89.0f; }
	if (pitch < -89.0f) { pitch = -89.0f; }

	//4.calculate the dir vector
	camDir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	camDir.y = -sin(glm::radians(pitch));
	camDir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	camFront = glm::normalize(camDir);
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
	fov -= (float)yOffset;
	if (fov < 1.0f) { fov = 1.0f; }
	if (fov > 45.0f) { fov = 45.0f; }
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