#include <iostream>
#include "Particle.h"
#include "Plane.h"
#include"Point.h"

void main(){
	Particle p(0.0f, 10.0f, 0.0f);
	Point point(0, 0, 0);
	Plane plane(point, glm::vec3(0,1,0));
	float dt = 0.01f;
	float tini = 0.0f;
	float tfinal = 10.0f;
	p.setLifetime(40.0f);
	std::cout << "Lifetime =" << p.getLifetime() << std::endl;
	p.setBouncing(0.8f);
	p.addForce(0, -9.8f, 0);
	p.setVelocity(0, 1, 0);
	//	p.setFixed(true);

	int count = 0;
	for (float t = tini; t <= tfinal; t += dt){
		p.updateParticle(dt, Particle::UpdateMethod::EulerSemi);
		std::cout << "posicio = " << p.getCurrentPosition().x << "  " << p.getCurrentPosition().y
			<< "  " << p.getCurrentPosition().z << "  temps = " << t << std::endl;
		//Check Floor collisions
		if (p.didCollidePlane(plane)) { //only valid for the plane y=0 (floor plane)
			p.setPosition(p.getCurrentPosition().x, -p.getCurrentPosition().y, p.getCurrentPosition().z);
			p.setVelocity(p.getVelocity().x, -p.getVelocity().y, p.getVelocity().z);
			std::cout << "rebot = " << count++ << std::endl;
			system("PAUSE");
		}
	}
	system("PAUSE");
}