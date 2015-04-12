#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include <math.h>
#include "Cube.h"
#include "Sphere.h"
#include "Triangle.h"

class Particle
{
public:
	enum class UpdateMethod : std::int8_t { EulerOrig, EulerSemi, Verlet };

	Particle();
	Particle(const float& x, const float& y, const float& z);
	~Particle();

	//setters
	void setPosition(const float& x, const float& y, const float& z);
	void setPosition(glm::vec3 pos);
	void setPreviousPosition(const float& x, const float& y, const float& z);
	void setPreviousPosition(glm::vec3 pos);
	void setVelocity(const float& x, const float& y, const float& z);
	void setVelocity(glm::vec3 vel);
	void setForce(const float& x, const float& y, const float& z);
	void setForce(glm::vec3 force);
	void setBouncing(float bouncing);
	void setLifetime(float lifetime);
	void setFixed(bool fixed);

	//getters
	glm::vec3 getCurrentPosition();
	glm::vec3 getPreviousPosition();
	glm::vec3 getForce();
	glm::vec3 getPreviousVelocity();
	glm::vec3 getVelocity();
	float getBouncing();
	float getLifetime();
	bool isFixed();

	//functions
	void addForce(glm::vec3 force);
	void addForce(const float& x, const float& y, const float& z);
	void updateParticle(const float& dt, UpdateMethod method = UpdateMethod::EulerOrig);
	void updateSpring(Particle &p, float ke, float kd, float longitud);

	void cubeCollision(const Cube &c);
	void triangleCollision(const Triangle &t);
	void sphereCollision(const Sphere &s);
private:
	glm::vec3 m_currentPosition;
	glm::vec3 m_previousPosition;
	glm::vec3 m_previousVelocity;
	glm::vec3 m_force;
	glm::vec3 m_velocity;

	float m_bouncing;
	float m_lifetime;
	bool  m_fixed;
};

