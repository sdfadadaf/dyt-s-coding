#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera
{
public:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;
	glm::mat4 view;	
	float speed;
	float sensitivity;
	float lastX;
	float lastY;
	float fov;
	Camera()
	{
		view = glm::mat4(1.0f);
		cameraPos = glm::vec3(0.0f, 0.0f, 6.0f);
		cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		speed = 1.5f;
		sensitivity = 0.05f;
		lastX = 100;
		lastY = 100;
		firstMouse = true;
		yaw = -90.0f;
		pitch = 0;
		fov = 45.0f;
		noFlyMode = false;
	}
	glm::mat4 getViewMatrix()
	{
		return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}

	void Move(Camera_Movement direc, float deltaTime)
	{
		float velocity = deltaTime * speed;
		glm::vec3 Displacement;
		if(direc == FORWARD)
			Displacement = cameraFront * velocity;
		if (direc == BACKWARD)
			Displacement = -cameraFront * velocity;
		if (direc == UP)
			Displacement = cameraUp * velocity;
		if (direc == DOWN)
			Displacement = -cameraUp * velocity;
		if (direc == LEFT)
			Displacement = -velocity * glm::normalize(glm::cross(cameraFront, cameraUp));
		if (direc == RIGHT)
			Displacement = velocity * glm::normalize(glm::cross(cameraFront, cameraUp));
		if (noFlyMode)
		{
			Displacement.y = 0.0f;
			Displacement = glm::normalize(glm::vec3(Displacement.x, 0.0f, Displacement.z)) * velocity;
		}
		cameraPos += Displacement;
	}
	
	void Towards(float posX, float posY)
	{
		if (firstMouse)
		{
			lastX = posX;
			lastY = posY;
			firstMouse = false;
		}
		float offsetX = (posX - lastX) * sensitivity;
		float offsetY = (lastY - posY) * sensitivity;
		lastX = posX;
		lastY = posY;
		
		yaw += offsetX;
		pitch += offsetY;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch > 89.0f)
			pitch = 89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
		direction.y = sin(glm::radians(pitch));
		direction.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
		cameraFront = glm::normalize(direction);
	}
	void Zoom(float offsetY)
	{
		fov -= offsetY;
		if (fov < 1.0f)
			fov = 1.0f;
		if (fov > 60.0f)
			fov = 60.0f;
	}

	void setNoFlyMode()
	{
		noFlyMode = true;
	}
	void setFlyMode()
	{
		noFlyMode = false;
	}

private:
	bool firstMouse;
	float yaw;
	float pitch;
	bool noFlyMode;
};