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
#include "Wave.h"
using namespace std;

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

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
	//corda 
	Wave wave;
	// particles
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// vertex bind
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0); // Unbind VAO

	// shadders
	// Create and compile the vertex shader
	std::string vContent = get_file_contents("./shaders/vertex-shader.txt");
	std::cout << vContent << std::endl;
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
	glEnable(GL_DEPTH_TEST);
	unsigned last = SDL_GetTicks();
	vector<GLfloat> vert(wave.size()*wave.size());
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glPointSize(10.0f);
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
				//else if (windowEvent.key.keysym.sym == SDLK_0) corda.reset(corda_mode(0));
				else if (windowEvent.key.keysym.sym == SDLK_0) { 
					wave.reset(5); 
				}
				else if (windowEvent.key.keysym.sym == SDLK_1) {
					wave.movePoint();
				}
				else if (windowEvent.key.keysym.sym == SDLK_2) {
					wave.moveWave();
				}
			}
		}
		SDL_GL_SwapWindow(window);
		unsigned current = SDL_GetTicks();
		//cout <<"frame length "<< current - last << endl;
		for (unsigned step = 0; step <= (current - last); ++step) {
			wave.updateVelocity(0.001f);
		}
		int delay = 16 - int(current - last);
		std::cout << current - last << std::endl;
		last = current;
		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Bind Textures using texture units
		glm::mat4 modelMatrix;
		GLint modelLoc = glGetUniformLocation(shaderProgram, "modelMatrix");
		GLint viewLoc = glGetUniformLocation(shaderProgram, "viewMatrix");
		GLint projLoc = glGetUniformLocation(shaderProgram, "projectionMatrix");
		GLint sizeLoc = glGetUniformLocation(shaderProgram, "size");
		GLint distLoc = glGetUniformLocation(shaderProgram, "dist");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniform1f(distLoc, CDIST);
		glUniform1i(sizeLoc, CSIZE);
		//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));
		//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera.getProjectionMatrix()));
		glm::mat4 view;
		GLfloat radius = 5.0f;
		GLfloat camX = sin(SDL_GetTicks() / 4000.0f) * radius;
		GLfloat camZ = cos(SDL_GetTicks() / 4000.0f) * radius;
		view = glm::lookAt(glm::vec3(camX, 10.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		// Projection 
		glm::mat4 projection;
		projection = glm::perspective(1.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		wave.loadVBO(vert);
		glBufferData(GL_ARRAY_BUFFER, vert.size()*sizeof(vert[0]), &vert[0], GL_STATIC_DRAW);
		glDrawArrays(GL_POINTS, 0, vert.size());
		glBindVertexArray(0);
		if (delay>0) SDL_Delay(delay);
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