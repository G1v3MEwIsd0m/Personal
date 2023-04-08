#include <camera.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <algorithm>




Camera::Camera(int width, int height, glm::vec3 initialPosition, bool isPerspective)
	:_isPerspective{ isPerspective }, 
	_position{ initialPosition }, 
	_lookDir{-1.f * initialPosition},
	_width{ width },
	_height{ height }  {

	recalculateVectors();
}

glm::vec3 Camera::GetPosition()
{
	return _position;
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(_position, _position + _lookDir, _upDir);
}

glm::mat4 Camera::GetProjectionMatrix() const{

	auto aspectRatio = (float)_width / (float)_height;
	if (_isPerspective) {
		return glm::perspective(glm::radians(_zoom),(float) _width / (float) _height, _near, _far);
	}
	return glm::ortho(-aspectRatio, aspectRatio, -1.f, 1.f, _near, _far);
}



void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = _movementSpeed * deltaTime;
	if (direction == ORTHO) {
		if (_isPerspective == false) {_isPerspective = true;}
		else{ _isPerspective = false; }	
	}
	if (direction == FORWARD) 
		_position += _lookDir * velocity;
	if (direction == BACKWARD)
		_position -= _lookDir * velocity;
	if (direction == LEFT)
		_position -= _sides * velocity;
	if (direction == RIGHT)
		_position += _sides * velocity;
	if (direction == UPWARD)
		_position += _upDir * velocity;
	if (direction == DOWNWARD)
		_position -= _upDir * velocity;
	
}

void Camera::RotateBy(float yaw, float pitch){
	_yaw += yaw;
	_pitch +=pitch;

	_pitch = std::clamp(_pitch, -89.f, 89.f);

	recalculateVectors();
}

void Camera::MoreZoom(float amount){

	_zoom -= amount;

	_zoom = std::clamp(_zoom, 1.f, 75.f);

}

void Camera::recalculateVectors() {
	_lookDir = glm::normalize(
		glm::vec3{
			std::cos(glm::radians(_yaw)) * cos(glm::radians(_pitch)),
			std::sin(glm::radians(_pitch)),
			std::sin(glm::radians(_yaw))* cos(glm::radians(_pitch))
		}
	);

	_upDir = glm::normalize(glm::cross(_sides, _lookDir));
}
