#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <iostream>
#include<stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"Camera.h"

const unsigned int width = 1600; //Window Width
const unsigned int height = 900; //Window Height

unsigned int VAO;
unsigned int VBO;
unsigned int lightVAO;

glm::vec3 lightClr = glm::vec3(1.0f);

unsigned int diffuseMap;
unsigned int specularMap;

glm::mat4 trans;

glm::mat4 model;
glm::mat4 view;
glm::mat4 proj;

Camera cam;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float lastX = width / 2;
float lastY = height / 2;
bool firstMouse = true;

glm::vec3 lightPos(1.0f, 1.0f, 4.0f);
glm::vec3 sunray = glm::vec3(-0.3f, -1.0f, -0.4f);

bool spot = false;
bool dir = false;
bool point = false;

float Kc = 1.0f;
float Kl = 0.09f;
float Kq = 0.032f;

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

	//Toggles
	static bool jLast = false;
	static bool kLast = false;
	static bool lLast = false;

	bool j = glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS;
	bool k = glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS;
	bool l = glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS;

	if (j && !jLast)
	{
		dir = !dir;
	}
	jLast = j;
	if (k && !kLast)
	{
		point = !point;
	}
	kLast = k;
	if (l && !lLast)
	{
		spot = !spot;
	}
	lLast = l;

	//Exit
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}