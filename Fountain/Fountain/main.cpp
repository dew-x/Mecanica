#include <GL\glew.h>
#include <SDL\SDL.h>
#include <SDL\SDL_opengl.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <time.h>
#include <vector>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Cube.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Particle.h"
#include "Corda.h"
using namespace std;

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
#define MAX_PARTICLES 2000
struct bs{
	unsigned begin, end;
};

enum mode {
	FOUNTAIN,
	CASCADE
};

float randClamp() {
	return float(rand()) / RAND_MAX;
}

std::string get_file_contents(std::string fname) {
	std::ifstream file(fname);
	if (file.fail())	{
		printf("FAIL Load file %s", fname.c_str());
	}

	//File contents stores all the text in the file
	std::string fileContents = "";
	//line is used to grab each line of the file
	std::string line;
	//Get all the lines in the file and add it to the contents
	while (getline(file, line)) {
		fileContents += line + "\n";
	}
	//Close the file
	file.close();
	return fileContents;
}

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_Window* window = SDL_CreateWindow("Fountain System", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(window);
	SDL_Event windowEvent;
	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();
	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);
	vector<GLfloat> vert = {
		0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f
	};
	// world
	Cube world({ -5, 0, -5 }, { 10, 10, 10 });
	vector<glm::vec3> tmpw = world.getQuads();
	for (unsigned i = 0; i < 12; ++i) {
		vert.push_back(tmpw[i].x);
		vert.push_back(tmpw[i].y);
		vert.push_back(tmpw[i].z);
		vert.push_back(0.0);
		vert.push_back(0.0);
		vert.push_back(0.5);
		vert.push_back(1.0f);
	}
	// sphere
	Point center({ 0, 0, 0 });
	Sphere sphere(center,2);
	vector<glm::vec3> tmps = sphere.getVertexSphere(10);
	for (unsigned i = 0; i < tmps.size(); ++i) {
		vert.push_back(tmps[i].x);
		vert.push_back(tmps[i].y);
		vert.push_back(tmps[i].z);
		vert.push_back(0.0);
		vert.push_back(0.5);
		vert.push_back(0.0);
		vert.push_back(1.0);
	}
	// plane
	Point p1(-0.5, 2, -3.5);
	Point p2(-3.5, 3, -0.5);
	Point p3(-0.5, 2.5, -0.5);
	
	
	Triangle tri(p1, p2, p3);
	vector<glm::vec3> tmpt=tri.getVertex();
	for (unsigned i = 0; i < tmpt.size(); ++i) {
		vert.push_back(tmpt[i].x);
		vert.push_back(tmpt[i].y);
		vert.push_back(tmpt[i].z);
		vert.push_back(0.5);
		vert.push_back(0.0);
		vert.push_back(0.0);
		vert.push_back(1.0);
	}
	// cube
	Cube cube({ -0.0f, 0.0f, -0.0f }, { 2.0f, 2.0f, 2.0f });
	vector<glm::vec3> tmpc = cube.getQuads();
	for (unsigned i = 0; i < tmpc.size(); ++i) {
		vert.push_back(tmpc[i].x);
		vert.push_back(tmpc[i].y);
		vert.push_back(tmpc[i].z);
		vert.push_back(0.5);
		vert.push_back(0.0);
		vert.push_back(0.0);
		vert.push_back(1.0);
	}
	for (unsigned i = 0; i < vert.size(); ++i) {
		if (i % 7 == 0) cout << endl;
		cout << vert[i] << " ";
	}
	//corda 
	Corda corda;
	// particles
	vector<Particle> particles(MAX_PARTICLES);
	for (unsigned i = 0; i < MAX_PARTICLES; ++i) {
		particles[i].setPosition({ 0.0f, 0.0f, 0.0f });
		particles[i].setForce({ 0.0f, 0.0f, 0.0f });
		particles[i].setBouncing(0.6f);
	}
	unsigned fid=0;
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// vertex bind
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vert.size()*sizeof(vert[0]), &vert[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0); // Unbind VAO

	// shadders
	// Create and compile the vertex shader
	std::string vContent = get_file_contents("./shaders/vertex-shader.txt");
	const char * vertexSource = vContent.c_str();
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	// Create and compile the fragment shader
	std::string fContent = get_file_contents("./shaders/fragment-shader.txt");
	const char * fragmentSource = fContent.c_str();
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	// Link the vertex and fragment shader into a shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	
	mode spawnMode = FOUNTAIN;
	/*GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
		5 * sizeof(float), 0);

	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
		5 * sizeof(float), (void*)(2 * sizeof(float)));*/
	glEnable(GL_DEPTH_TEST);
	unsigned last = SDL_GetTicks();
	while (true)
	{
		//glUniform3f(uniColor, (sin(SDL_GetTicks() / 200.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT) break;
			else if (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_ESCAPE) break;
			else if (windowEvent.type == SDL_MOUSEWHEEL) {
				// scale
			}
			else if (windowEvent.type == SDL_KEYDOWN) {
				if (windowEvent.key.keysym.sym == SDLK_UP || windowEvent.key.keysym.sym == SDLK_w) ;
				else if (windowEvent.key.keysym.sym == SDLK_LEFT || windowEvent.key.keysym.sym == SDLK_a) ;
				else if (windowEvent.key.keysym.sym == SDLK_DOWN || windowEvent.key.keysym.sym == SDLK_s) ;
				else if (windowEvent.key.keysym.sym == SDLK_RIGHT || windowEvent.key.keysym.sym == SDLK_d) ;
				else if (windowEvent.key.keysym.sym == SDLK_0) corda.reset(corda_mode(0));
				else if (windowEvent.key.keysym.sym == SDLK_1) { 
					corda.reset(corda_mode(1));
					spawnMode = FOUNTAIN; 
				}else if (windowEvent.key.keysym.sym == SDLK_2) { 
					corda.reset(corda_mode(2));
					spawnMode = CASCADE; 
				}
			}
		}
		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Bind Textures using texture units
		glm::mat4 modelMatrix;
		GLint modelLoc = glGetUniformLocation(shaderProgram, "modelMatrix");
		GLint viewLoc = glGetUniformLocation(shaderProgram, "viewMatrix");
		GLint projLoc = glGetUniformLocation(shaderProgram, "projectionMatrix");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));
		//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera.getProjectionMatrix()));
		glm::mat4 view;
		GLfloat radius = 5.0f;
		GLfloat camX = sin(SDL_GetTicks() / 1600.0f) * radius;
		GLfloat camZ = cos(SDL_GetTicks() / 1600.0f) * radius;
		view = glm::lookAt(glm::vec3(camX, 10.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		// Projection 
		glm::mat4 projection;
		projection = glm::perspective(1.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 1, vert.size()/7);
		/*for (unsigned i = 0; i < VOSIZE; ++i) {
			if (i == 0) glDrawArrays(GL_QUADS, LOC[i].begin, LOC[i].end);
			else if (i == 1) glDrawArrays(GL_TRIANGLES, LOC[i].begin, LOC[i].end);
			else if (i == 2) glDrawArrays(GL_POINT, LOC[i].begin, LOC[i].end);
		}*/
		for (unsigned i = 0; i < corda.size(); ++i) {
			glm::mat4 model;
			glm::vec3 pos = corda.getPos(i);
			model = glm::translate(model, pos);
			//GLfloat angle = 20.0f * i;
			//model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_POINTS, 0, 1);
		}
		glBindVertexArray(0);
		// Activate shader
		//glUseProgram(shaderProgram);

		// Camera/View transformation
		/*glm::mat4 view;
		GLfloat radius = 10.0f;
		GLfloat camX = sin(SDL_GetTicks()/800.0f) * radius;
		GLfloat camZ = cos(SDL_GetTicks() / 800.0f) * radius;
		view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		// Projection 
		glm::mat4 projection;
		projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
		GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
		GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(VAO);
		for (GLuint i = 0; i < 10; i++)
		{
			// Calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			GLfloat angle = 20.0f * i;
			model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);*/

		SDL_GL_SwapWindow(window);
		unsigned current = SDL_GetTicks();
		//cout <<"frame length "<< current - last << endl;
		if (spawnMode == FOUNTAIN) {
			// spawn particle
			unsigned pid = fid%MAX_PARTICLES;
			particles[pid].setPosition({ 0.0f, 2.1f, 0.0f });
			particles[pid].setForce({ 0.0f, -9.8f, 0.0f });
			particles[pid].setVelocity({ (randClamp() - 0.5)*2.5, 4.0f + randClamp() * 4.0f, (randClamp() - 0.5)*2.5 });
		}
		else if (spawnMode == CASCADE) {
			// spawn particle
			unsigned pid = fid%MAX_PARTICLES;
			particles[pid].setPosition({ 0.0f, 5.0f, 0.0f });
			particles[pid].setForce({ 0.0f, -9.8f, 0.0f });
			particles[pid].setVelocity({ (randClamp() - 0.5)*2.5, 0.0f, (randClamp() - 0.5)*2.5 });
		}
		for (unsigned step = 0; step < (current - last); ++step) {
			for (unsigned i = 0; i < corda.size(); ++i) {
				Particle *p = corda.getPart(i);
				p->updateParticle(0.001f,Particle::UpdateMethod::EulerSemi);
				p->cubeCollision(world);
				p->cubeCollision(cube);
				p->triangleCollision(tri);
				p->sphereCollision(sphere);
			}
			/*unsigned dist = (current - last) % 10;
			particles[i].updateParticle(0.001f*dist, Particle::UpdateMethod::EulerSemi);
			particles[i].cubeCollision(world);
			particles[i].cubeCollision(cube);
			particles[i].triangleCollision(tri);
			particles[i].sphereCollision(sphere);*/
		}
		last = current;
		++fid;
	}
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	
	SDL_DestroyWindow(window);
	SDL_GL_DeleteContext(context);
	SDL_Quit();
	return 0;
}