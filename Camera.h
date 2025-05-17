#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include<glm/glm.hpp>
#include<glad/glad.h>
#include<glm/gtc/matrix_transform.hpp>

enum CamMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.05f;
const float ZOOM = 45.0f;

class Camera
{
public:
	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	float yaw;
	float pitch;

	float speed;
	float sensitivity;
	float zoom;

	//vector constructor
	Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : 
		front(glm::vec3(0.0f, 0.0f, -1.0f)), speed(SPEED), sensitivity(SENSITIVITY), zoom(ZOOM)
	{
		this->pos = pos;
		this->worldUp = up;
		this->yaw = yaw;
		this->pitch = pitch;

		updateCameraVectors();
	}

	//scalar constructor
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : 
		front(glm::vec3(0.0f, 0.0f, -1.0f)), speed(SPEED), sensitivity(SENSITIVITY), zoom(ZOOM)
	{
		this->pos = glm::vec3(posX, posY, posZ);
		this->worldUp = glm::vec3(upX, upY, upZ);
		this->yaw = yaw;
		this->pitch = pitch;

		updateCameraVectors();
	}

	//functions
	//returns view matrix
	glm::mat4 getViewMatrix()
	{
		return glm::lookAt(pos, pos + front, up);
	}

	//processes keyboard inputs
	void ProcessKeyboard(CamMovement dir, float deltaTime)
	{
		float vel = speed * deltaTime;
		if (dir == FORWARD)
		{
			pos += front * vel;
		}
		if (dir == BACKWARD)
		{
			pos -= front * vel;
		}
		if (dir == LEFT)
		{
			pos -= right * vel;
		}
		if (dir == RIGHT)
		{
			pos += right * vel;
		}

	}

	//processes mouse inputs
	void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true)
	{
		xOffset *= sensitivity;
		yOffset *= sensitivity;

		yaw += xOffset;
		pitch += yOffset;

		if (constrainPitch)
		{
			if (pitch > 89.0f) { pitch = 89.0f; }
			if (pitch < -89.0f) { pitch = -89.0f; }
		}

		updateCameraVectors();
	}

	//processes scroll input
	void ProcessScroll(float yOffset)
	{
		zoom -= yOffset;
		if (zoom > 45.0f) { zoom = 45.0f; }
		if (zoom < 1.0f) { zoom = 1.0f; }
	}

private:
	//calculate and update camera vectors
	void updateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) *cos(glm::radians(pitch));
		front.y = -sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) *cos(glm::radians(pitch));
		this->front = glm::normalize(front);

		right = glm::normalize(glm::cross(this->front, worldUp));
		up = glm::normalize(glm::cross(right, this->front));
	}
};

#endif 