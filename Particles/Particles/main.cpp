#include <GL\glew.h>
#include <SDL\SDL.h>
#include <SDL\SDL_opengl.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <time.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define WIDTH 800
#define HEIGHT 600

SDL_GLContext context;
SDL_Window* window;

void init_world() {

}

void init_particles() {

}

void init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	window = SDL_CreateWindow("OpenGL", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(window);
	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();
	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	init_world();
	init_particles();
}

void update() {

}

void checkEnd(bool &end) {
	SDL_Event windowEvent;
	while (SDL_PollEvent(&windowEvent))
	{
		if (windowEvent.type == SDL_QUIT) end = true;
		else if (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_ESCAPE) end = true;
	}
}

void end() {
	SDL_DestroyWindow(window);
	SDL_GL_DeleteContext(context);
	SDL_Quit();
}

int main(int argc, char *argv[]) {
	bool ended = false;
	init();
	while (!ended) {
		update();
		checkEnd(ended);
	}
	end();
	return 0;
}