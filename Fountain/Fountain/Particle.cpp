#include "Particle.h"


Particle::Particle()
{
	m_lifetime = -1;
}

Particle::Particle(const float& x, const float& y, const float& z) :
m_previousPosition(0, 0, 0), m_velocity(0, 0, 0), m_force(0, 0, 0), m_bouncing(1), m_lifetime(50), m_fixed(false)
{
	m_currentPosition.x = x;
	m_currentPosition.y = y;
	m_currentPosition.z = z;

}

/*
Particle::Particle(glm::vec3 pos, glm::vec3 vel, float bouncing, bool fixed, int lifetime, glm::vec3 force) :
m_currentPosition(pos), m_previousPosition(pos), m_force(force), m_velocity(vel), m_bouncing(bouncing), m_lifetime(lifetime), m_fixed(fixed)
{
}
*/

Particle::~Particle()
{
}

//setters
void Particle::setPosition(const float& x, const float& y, const float& z)
{
	glm::vec3 pos;
	pos.x = x; pos.y = y; pos.z = z;
	m_currentPosition = pos;
}
void Particle::setPosition(glm::vec3 pos)
{
	m_currentPosition = pos;
}

void Particle::setPreviousPosition(const float& x, const float& y, const float& z)
{
	glm::vec3 pos;
	pos.x = x; pos.y = y; pos.z = z;
	m_previousPosition = pos;
}

void Particle::setPreviousPosition(glm::vec3 pos)
{
	m_previousPosition = pos;
}

void Particle::setForce(const float& x, const float& y, const float& z)
{
	glm::vec3 force;
	force.x = x; force.y = y; force.z = z;
	m_force = force;
}

void Particle::setForce(glm::vec3 force)
{
	m_force = force;
}

void Particle::addForce(const float& x, const float& y, const float& z)
{
	glm::vec3 force;
	force.x += x; force.y += y; force.z += z;
	m_force += force;
}

void Particle::addForce(glm::vec3 force)
{
	m_force += force;
}

void Particle::setVelocity(const float& x, const float& y, const float& z)
{
	glm::vec3 vel;
	vel.x = x; vel.y = y; vel.z = z;
	m_velocity = vel;
}

void Particle::setVelocity(glm::vec3 vel)
{
	m_velocity = vel;
}

void Particle::setBouncing(float bouncing)
{
	m_bouncing = bouncing;
}

void Particle::setLifetime(float lifetime)
{
	m_lifetime = lifetime;
}

void Particle::setFixed(bool fixed)
{
	m_fixed = fixed;
}

//getters
glm::vec3 Particle::getCurrentPosition()
{
	return m_currentPosition;
}

glm::vec3 Particle::getPreviousPosition()
{
	return m_previousPosition;
}

glm::vec3 Particle::getForce()
{
	return m_force;
}

glm::vec3 Particle::getPreviousVelocity()
{
	return m_previousVelocity;
}

glm::vec3 Particle::getVelocity()
{
	return m_velocity;
}

float Particle::getBouncing()
{
	return m_bouncing;
}

float Particle::getLifetime()
{
	return m_lifetime;
}

bool Particle::isFixed()
{
	return m_fixed;
}

void Particle::updateParticle(const float& dt, UpdateMethod method)
{
		switch (method)
		{
			case UpdateMethod::EulerOrig:
				m_previousPosition = m_currentPosition;
				m_previousVelocity = m_velocity;
				m_currentPosition += m_velocity*dt;
				m_velocity += m_force*dt;
				m_lifetime--;
				break;
			case UpdateMethod::EulerSemi:
				m_previousPosition = m_currentPosition;
				m_previousVelocity = m_velocity;
				m_velocity += m_force*dt;
				m_currentPosition += m_velocity*dt;
				m_lifetime--;
				break;
			case UpdateMethod::Verlet:
				m_previousPosition = m_currentPosition;
				m_previousVelocity = m_velocity;
				m_currentPosition += (m_currentPosition - m_previousPosition) + m_force*((dt*dt)/1.0f);
				m_velocity = (m_currentPosition - m_previousPosition)/dt;
				m_lifetime--;
				break;
			default:
				break;
		}
}


void Particle::updateSpring(Particle &p, float ke, float kd, float longitud) {
	glm::vec3 force = (ke*(glm::length(p.m_currentPosition - m_currentPosition) - longitud) + kd * glm::dot((p.m_velocity - m_velocity), glm::normalize(p.m_currentPosition - m_currentPosition)))*glm::normalize(p.m_currentPosition - m_currentPosition);
	setForce(force);	
	p.setForce(-force);
	p.addForce(0, -9.8f, 0);
}

void Particle::cubeCollision(const Cube &c) {

}
void Particle::triangleCollision(const Triangle &t) {

}
void Particle::sphereCollision(const Sphere &s) {

}