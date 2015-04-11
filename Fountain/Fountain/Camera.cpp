#include "Camera.h"

Camera::Camera()
{
	_near = _far = _FOV = _projectionWidth = _projectionHeight = _aspectRatio = 0.0f;
	_cameraPos = _cameraFront = _cameraUp = { 0.0f, 0.0f, 0.0f };
}

Camera::~Camera()
{
}

void Camera::setRatio(const float & width, const float & height) {
	_projectionWidth = width / 100;
	_projectionHeight = height / 100;
	_aspectRatio = width / height;
}

void Camera::setPlanes(const float & n, const float & f) {
	_near = n;
	_far = f;
}

void Camera::setCamera(int mode) {
	(mode == 0) ? ortographicMode() : perspectiveMode();
	glm::vec3 cameraDirection = glm::normalize(_cameraPos - _cameraFront);
	glm::vec3 up = { 0.0f, 0.0f, 1.0f };
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	_cameraUp = glm::cross(cameraDirection, cameraRight);
	_viewMatrix = glm::lookAt(_cameraPos, _cameraFront, _cameraUp);
}
