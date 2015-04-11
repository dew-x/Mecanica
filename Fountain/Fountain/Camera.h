#pragma once
#include <GL/glew.h>					//The OpenGL Extension Wrangler
#include <glm/glm.hpp>					//OpenGL Mathematics 
#include <glm/gtc/matrix_transform.hpp> //OpenGL Matrix transform functions

class Camera
{
	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;
	float _FOV;
	float _far;
	float _near;
	float _projectionWidth;
	float _projectionHeight;
	float _aspectRatio;
	glm::vec3 _cameraPos;
	glm::vec3 _cameraFront;
	glm::vec3 _cameraUp;
	inline void ortographicMode() { _projectionMatrix = glm::ortho(-_projectionWidth / 2, _projectionWidth / 2, -_projectionHeight / 2, _projectionHeight / 2, _near, _far); };
	inline void perspectiveMode() { _projectionMatrix = glm::perspective(_FOV, (float)_aspectRatio, _near, _far); };
public:
	Camera();
	~Camera();
	//setters
	void setRatio(const float & width, const float & height);
	void setPlanes(const float & n, const float & f);
	inline void setPos(const float & x, const float & y, const float & z) { _cameraPos = { x, y, z }; };
	inline void setFront(const float & x, const float & y, const float & z) { _cameraFront = { x, y, z }; };
	inline void setDepth(const float & n) { _FOV = n; };
	void setCamera(int mode); // 0=ortographic, 1=perspective
	//getters
	inline glm::mat4 &getProjectionMatrix() { return _projectionMatrix; };
	inline glm::mat4 &getViewMatrix() { return _viewMatrix; };
};

