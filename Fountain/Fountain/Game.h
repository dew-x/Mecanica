#pragma once


//Third-party libraries
#include <GL/glew.h>			//The OpenGL Extension Wrangler
#include <glm/glm.hpp>			//OpenGL Mathematics 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <time.h>

#include "Window.h"
#include "GLSLProgram.h"
#include "FPSLimiter.h"
#include "OpenGLBuffers.h"
#include "Geometry.h"
#include "Camera.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Particle.h"

#define GLM_FORCE_RADIANS
#define _USE_MATH_DEFINES
#define MAX_PLANES 5
#define MAX_PARTICLES 30
#define MAX_OBJECTS 8

//Game has three possible states: INIT (Preparing environment), PLAY (Playing) or EXIT (Exit from the game)
enum class GameState{ INIT, PLAY, EXIT };

//This class manages the game execution
class Game {
public:
	Game(std::string windowTitle, int screenWidth, int screenHeight, bool enableLimiterFPS, int maxFPS, bool printFPS);	//Constructor
	~Game();					//Destructor
	void run();					//Game execution


private:
	//Attributes	
	std::string _windowTitle;		//Window Title
	int _screenWidth;				//Screen width in pixels				
	int _screenHeight;				//Screen height in pixels				
	GameState _gameState;			//It describes the game state				
	Window _window;					//Manage the OpenGL context
	GLSLProgram _colorProgram;		//Manage the shaders
	FPSLimiter _fpsLimiter;			//Manage the synchronization between frame rate and refresh rate
	OpenGLBuffers _openGLBuffers;	//Manage the openGL buffers
	Geometry _objectData;
	Camera _camera;
	Sphere sphere;
	Triangle triangle;
	Plane plane[MAX_PLANES];
	Particle pSystem[MAX_PARTICLES];

	//Internal methods
	void initSystems();
	void loadShaders();
	void createPrimitivesToRender();
	void gameLoop();
	void processKeyPressed(int keyType, bool keyPressed);
	void processMousePressed(unsigned char button, bool keyPressed);
	void processInput();
	void updateGameObjects();
	void drawGame();
	void loadObjects(string filename);
	void initPartSystem();

	//Internal atributes
	bool keypressedW = false;
	bool keypressedA = false;
	bool keypressedS = false;
	bool keypressedD = false;
	bool mousepressedL = false;
	bool mousepressedR = false;
	glm::vec3 camTranslate = { 0.0f, 0.0f, 0.0f };
	float camAngle = 0.0f;
	glm::vec3 camRotate = { 0.0f, 0.0f, 1.0f };
	glm::vec3 camScale = { 1.0f, 1.0f, 1.0f };
	float mouseLastPosX = 0, mouseLastPosY = 0;
	int systMode = 1;
	bool fixParticles = false;
};

