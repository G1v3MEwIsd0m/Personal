#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>


class Camera {
	
public:
	enum Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UPWARD,
		DOWNWARD,
		ORTHO
	};

	explicit Camera(int width, int height, glm::vec3 initialPosition = glm::vec3 { 0.f, 0.f, 3.f },bool isPerpective = true);
	
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix() const;
	glm::vec3 GetPosition();
	
	
	void SetAspectRatio(float aspectRation) { _aspectRatio = aspectRation;}

	bool isPerspective() const { return _isPerspective; }
	
	void SetSize(int width, int height) {
		_width = width;
		_height = height;
	}

	void ProcessKeyboard(Camera_Movement direction, float deltaTime);//MoveCamera with keyboard

	void RotateBy(float yaw, float pitch);
	void MoreZoom(float amount);

private:
	void recalculateVectors();
private:
	bool _isPerspective{ true };

	glm::vec3 _position {};//cameraPos
	glm::vec3 _lookDir {};//camerafront
	glm::vec3 _upDir {0.f, 1.f, 0.f};//cameraUp


	glm::vec3 _sides = glm::normalize(glm::cross(_lookDir, _upDir));
	float _yaw{};
	float _pitch{};
	

	
	float _movementSpeed = 20.5f;
	float _mouseSensitivity = 0.1;

	int _width{ 0 };
	int _height{ 0 };
	float _aspectRatio{ (0.f) };
	float _near{ 0.1f };
	float _far{ 100.f };

	float _zoom{ 75.0f };

	};