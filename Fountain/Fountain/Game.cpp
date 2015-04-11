#include "Game.h"


/**
* Constructor
* Note: It uses an initialization list to set the parameters
* @param windowTitle is the window title
* @param screenWidth is the window width
* @param screenHeight is the window height
*/
Game::Game(std::string windowTitle, int screenWidth, int screenHeight, bool enableLimiterFPS, int maxFPS, bool printFPS) :
_windowTitle(windowTitle),
_screenWidth(screenWidth),
_screenHeight(screenHeight),
_gameState(GameState::INIT),
_fpsLimiter(enableLimiterFPS, maxFPS, printFPS) {


}

/**
* Destructor
*/
Game::~Game()
{
}

/*
* Game execution
*/
void Game::run() {
	//System initializations
	initSystems();
	//Start the game if all the elements are ready
	gameLoop();
}

void Game::initPartSystem() {
	for (int i = 0; i < MAX_PARTICLES; i++) {
		if (pSystem[i].getLifetime() < 0) {
			//WATERFALL
			if (systMode == 1) {
				pSystem[i].setForce(0.0f, 0.0f, 0.0f);
				pSystem[i].setPosition(0.0f, 0.0f, 2.0f);
				pSystem[i].setVelocity((double)rand() / (double)RAND_MAX - 0.5f, (double)rand() / (double)RAND_MAX - 0.5f, -rand() % 3);
				pSystem[i].setLifetime(rand() % 100 + 100);
				pSystem[i].setBouncing(0.8f);
				pSystem[i].addForce(0.0f, 0.0f, -9.8f);
			}
			//FOUNTAIN
			else if (systMode == 2) {
				pSystem[i].setForce(0.0f, 0.0f, 0.0f);
				pSystem[i].setPosition(0.0f, 0.0f, 1.0f);
				pSystem[i].setVelocity((double)rand() / (double)RAND_MAX - 0.5f, (double)rand() / (double)RAND_MAX - 0.5f, rand() % 5 + 2);
				pSystem[i].setLifetime(rand() % 100 + 100);
				pSystem[i].setBouncing(0.8f);
				pSystem[i].addForce(0.0f, 0.0f, -9.8f);
			}
		}
	}
}

/*
* Initializes all the game engine components
*/
void Game::initSystems() {
		//Create an Opengl window using SDL
	_window.create(_windowTitle, _screenWidth, _screenHeight, 0);
		//Compile and Link shader
	loadShaders();
		//Load the current scenario
	_openGLBuffers.initializeBuffers(_colorProgram);
		//Create several vertex
	createPrimitivesToRender();
		//Initialize the different primitives
	_objectData.initPrimitives();

	cout << endl << "==================================================" << endl;
	cout << "JORDI SERRANO'S PARTICLE SYSTEM" << endl;
	cout << "==================================================" << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "MODES" << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "- Press 1 to set a Waterfall system." << endl;
	cout << "- Press 2 to set a Fountain system." << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "CONTROLS" << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "- WASD or arrows to move the camera in the world space." << endl;
	cout << "- E to move up and Q to move down." << endl;
	cout << "- Click and drag the mouse to rotate the camera." << endl;
	cout << "- Hold spacebar to freeze particles." << endl;

		//Initialize the camera attributes
	_camera.setPlanes(0.1f, 100.0f);
	_camera.setDepth(90.0f);
	_camera.setPos(3.0f, 0.0f, 2.0f);

		//Initialize the sphere attributes
	sphere.setCenter(_objectData.getObject()[5]._translation);
	sphere.setRadius(0.795f);

		//Initialize the planes attributes
	plane[0].setNormal(0.0f, 0.0f, 1.0f);
	plane[0].setPoint(0.0f, 0.0f, 0.0f);
	plane[1].setNormal(-1.0f, 0.0f, 0.0f);
	plane[1].setPoint(2.0f, 0.0f, 0.0f);
	plane[2].setNormal(0.0f, -1.0f, 0.0f);
	plane[2].setPoint(0.0f, 2.0f, 0.0f);
	plane[3].setNormal(1.0f, 0.0f, 0.0f);
	plane[3].setPoint(-2.0f, 0.0f, 0.0f);
	plane[4].setNormal(0.0f, 1.0f, 0.0f);
	plane[4].setPoint(0.0f, -2.0f, 0.0f);
	for (int i = 0; i < 5; i++) plane[i].computeD();
	
		//Initialize the triangle attributes
	triangle.setVertices({ -1.0f, 0.0f, 1.0f }, { 0.0f, -2.0f, 1.0f }, { -2.0f, -2.0f, 1.0f });
	triangle.computeNormal();
	triangle.computeD();

		//Initialize the particles attributes
	initPartSystem();
}

/*
* Compiles, sets the variables between C++ and the Shader program and links the shader program
*/
void Game::loadShaders() {
	//Compile the shaders
	_colorProgram.addShader(GL_VERTEX_SHADER, "./resources/shaders/vertex-shader.txt");
	_colorProgram.addShader(GL_FRAGMENT_SHADER, "./resources/shaders/fragment-shader.txt");
	_colorProgram.compileShaders();
	//Attributes must be added before linking the code
	_colorProgram.addAttribute("vertexPositionGame");
	_colorProgram.addAttribute("vertexColor");
	//Link the compiled shaders
	_colorProgram.linkShaders();
}

/**
* Initialize the position and the color of the different vertices that have to be rendered
*/
void Game::createPrimitivesToRender() {
	_objectData.LoadScene("./resources/gameObjects.txt");
}

/*
* Game execution: Gets input events, processes game logic and draws sprites on the screen
*/
void Game::gameLoop() {
	_gameState = GameState::PLAY;
	while (_gameState != GameState::EXIT) {
		//Start synchronization between refresh rate and frame rate
		_fpsLimiter.startSynchronization();
		//Process the input information (keyboard and mouse)
		processInput();
		//Execute pending actions
		updateGameObjects();
		//Draw the objects on the screen
		drawGame();
		//Force synchronization
		_fpsLimiter.forceSynchronization();
	}
}

/*
* Processes keyboard input
*/
void Game::processKeyPressed(int keyType, bool keyPressed) {
	if (keyType == SDLK_ESCAPE) _gameState = GameState::EXIT;
	if (keyType == SDLK_UP || keyType == SDLK_w) keypressedW = keyPressed ? true : false;
	if (keyType == SDLK_LEFT || keyType == SDLK_a) keypressedA = keyPressed ? true : false;
	if (keyType == SDLK_DOWN || keyType == SDLK_s) keypressedS = keyPressed ? true : false;
	if (keyType == SDLK_RIGHT || keyType == SDLK_d) keypressedD = keyPressed ? true : false;
	if (keyType == SDLK_e) camTranslate.z -= 0.02f;
	if (keyType == SDLK_q) camTranslate.z += 0.02f;
	if (keyType == SDLK_1) systMode = 1; for (int i = 0; i < MAX_PARTICLES; i++) pSystem[i].setLifetime(1.0f);
	if (keyType == SDLK_2) systMode = 2; for (int i = 0; i < MAX_PARTICLES; i++) pSystem[i].setLifetime(1.0f);
	if (keyType == SDLK_SPACE) fixParticles = keyPressed ? true : false;
	//cout << "posX: " << camPosX << "  posY: " << camPosY << "  posZ: " << camPosZ << endl;
}


/*
* Processes mouse input
*/
void Game::processMousePressed(unsigned char button, bool keyPressed) {
	if (button == SDL_BUTTON_LEFT) mousepressedL = keyPressed ? true : false;
	if (button == SDL_BUTTON_RIGHT) mousepressedR = keyPressed ? true : false;
}

/*
* Processes input with SDL
*/
void Game::processInput() {
	//Review https://wiki.libsdl.org/SDL_Event to see the different kind of events
	//Moreover, table show the property affected for each event type
	SDL_Event evnt;
	int mouseX, mouseY;
	float mousePosX, mousePosY;
	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			//cout << "(" << evnt.motion.x << ", " << evnt.motion.y << ")" << endl;
			break;
		case SDL_MOUSEBUTTONUP:
			processMousePressed(evnt.button.button, false);
			break;
		case SDL_MOUSEBUTTONDOWN:
			processMousePressed(evnt.button.button, true);
			break;
		case SDL_MOUSEWHEEL:
			camScale += (evnt.wheel.y < 0.0f) ? -0.05f : 0.05f;
			if (camScale.x <= 0.15f && camScale.y <= 0.15f && camScale.z <= 0.15f) camScale += glm::vec3(0.05f, 0.05f, 0.05f);
			if (camScale.x >= 10.0f && camScale.y >= 10.0f && camScale.z >= 10.0f) camScale -= glm::vec3(0.05f, 0.05f, 0.05f);
			//cout << "scX: " << scaleVec.x << "  scY: " << scaleVec.y << "  scZ: " << scaleVec.z << endl;
			break;
		case SDL_KEYDOWN:
			processKeyPressed(evnt.key.keysym.sym, true);
			break;
		case SDL_KEYUP:
			processKeyPressed(evnt.key.keysym.sym, false);
			break;
		default:
			break;
		}
		// -----------------------  EXECUTE INPUT ACTIONS  --------------------------
		if (keypressedW) camTranslate.x += 0.02f;
		if (keypressedA) camTranslate.y += 0.02f;
		if (keypressedS) camTranslate.x -= 0.02f;
		if (keypressedD) camTranslate.y -= 0.02f;
		if (mousepressedL) {
			SDL_GetMouseState(&mouseX, &mouseY);
			mousePosX = (float)(mouseX - _screenWidth / 2) / (_screenWidth / 2);
			mousePosY = (float)(mouseY - _screenHeight / 2) / (_screenHeight / 2);
			camAngle += (mouseLastPosX<mousePosX) ? 180.0f : -180.0f;
			mouseLastPosX = mousePosX;
		}
	}
}

/**
* Draw the sprites on the screen
*/
void Game::drawGame() {
	//Set the base depth to 1.0
	glClearDepth(1.0);

	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Bind the GLSL program. Only one code GLSL can be used at the same time
	_colorProgram.use();

	//Create model matrix
	GLuint modelMatrixUniform = _colorProgram.getUniformLocation("modelMatrix");
	//Create view matrix
	GLuint viewMatrixUniform = _colorProgram.getUniformLocation("viewMatrix");
	//Create projection matrix
	GLuint projectionMatrixUniform = _colorProgram.getUniformLocation("projectionMatrix");

	// ------------------------------------------------------------------------------
	// ---------------------------------  CAMERA   ----------------------------------
	// ------------------------------------------------------------------------------
	// ----------------------------  ORTOGRAPHIC MODE  ------------------------------
	//_camera.setRatio(_screenWidth, _screenHeight);
	//_camera.setCamera(0);
	// ----------------------------  PERSPECTIVE MODE  ------------------------------
	_camera.setRatio(_screenWidth, _screenHeight);
	_camera.setCamera(1);
	// ---------------------------  CAMERA INTERACTION  -----------------------------
	_camera.getViewMatrix() = glm::translate(_camera.getViewMatrix(), camTranslate);
	if (camAngle != 0)_camera.getViewMatrix() = glm::rotate(_camera.getViewMatrix(), glm::radians(camAngle), camRotate);
	_camera.getViewMatrix() = glm::scale(_camera.getViewMatrix(), camScale);

	// ------------------------------------------------------------------------------
	// ------------------------------  DISPLAY DATA   -------------------------------
	// ------------------------------------------------------------------------------
	initPartSystem();
	for (int i = 0; i < MAX_PARTICLES; i++) {
		pSystem[i].setFixed((fixParticles) ? true : false);
		// ------------------------  PARTICLE UPDATE  ------------------------------
		pSystem[i].updateParticle(0.01f, Particle::UpdateMethod::EulerSemi);
		_objectData.getObject()[i + MAX_OBJECTS]._translation = pSystem[i].getCurrentPosition();
		// ----------------------  PARTICLE COLLISIONS  ----------------------------
		pSystem[i].collideWithSphere(sphere);
		pSystem[i].collideWithTriangle(triangle);
		for (int n = 0; n < MAX_PLANES; n++) pSystem[i].collideWithPlane(plane[n]);
	}

	for (int i = 0; i < _objectData.getNumObjects(); i++) {
		glm::mat4 modelMatrix; //Identity matrix (Translate*Rotate*Scale)
		// ----------------------  OBJECTS' TRANSLATION  ----------------------------
		modelMatrix = glm::translate(modelMatrix, _objectData.getObject()[i]._translation);
		// ------------------------  OBJECTS' ROTATION  -----------------------------
		if (_objectData.getObject()[i]._angle != 0) modelMatrix = glm::rotate(modelMatrix, glm::radians(_objectData.getObject()[i]._angle), _objectData.getObject()[i]._rotation);
		// -------------------------  OBJECTS' SCALE  -------------------------------
		modelMatrix = glm::scale(modelMatrix, _objectData.getObject()[i]._scale);
		// --------------------------  MVP MATRICES  --------------------------------
		glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, glm::value_ptr(_camera.getViewMatrix()));
		glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(_camera.getProjectionMatrix()));
		// ---------------------------  SEND DATA -----------------------------------
		_openGLBuffers.sendDataToGPU(_objectData.getData(_objectData.getObject()[i]._objectType), _objectData.getNumVertices(_objectData.getObject()[i]._objectType), _objectData.getObject()[i]._mode);
	}

	//Unbind the program
	_colorProgram.unuse();

	//Swap the display buffers (displays what was just drawn)
	_window.swapBuffer();
}

/*
* Execute the actions that must update the game objects
*/
void Game::updateGameObjects() {


}