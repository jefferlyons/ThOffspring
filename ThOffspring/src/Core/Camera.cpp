#include "Camera.h"


Camera::~Camera()
{
}

mat4 Camera::GetViewMatrix()
{
	return lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(Camare_Movemnt direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
		Position += Front * velocity;
	if (direction == BACKWARD)
		Position -= Front * velocity;
	if (direction == LEFT)
		Position -= Right * velocity;
	if (direction == RIGHT)
		Position += Right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
	vec3 front;
	front.x = cos(radians(Yaw) * cos(radians(Pitch)));
	front.y = sin(radians(Pitch));
	front.z = sin(radians(Yaw) * cos(radians(Pitch)));

	Front = normalize(front);
	Right = normalize(cross(Front, WorldUp));
	Up =    normalize(cross(Right, Front));
}
