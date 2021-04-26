#pragma once
#include <iostream>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTCallbacks.h"
#include <time.h>
#include <math.h>
#include <corecrt_math_defines.h>
#include <string>
#include "Cube.h"
#include "Pyramid.h"
#include "MeshLoader.h"
#include "Player.h"
#include "GenericObject.h"
#include "Checkpoint.h"
#define REFRESH_RATE 16

class Source
{
private:
	Camera* camera;

	// Directional Light
	Vector4* _lightPosition;
	Lighting* _lightData;

	// Scene Objects
	SceneObject* _root;
	Checkpoint* _checkpoints[10];
	Player* _player;

	// Player Variables
	int _player_checkpoint = 0;
	int _player_lap = 1;

	// Player Movement Variables
	bool _player_forwards = false;
	bool _player_backwards = false;
	bool _player_left = false;
	bool _player_right = false;
	bool _player_up = false;
	bool _player_down = false;
	bool _player_rotateLeft = false;
	bool _player_rotateRight = false;

	clock_t start_time;
public:
	// Constructors and Deconstructors
	Source(int argc, char* argv[]);
	~Source(void);

	// Init Methods
	void InitObjects();
	void InitGL(int argc, char* argv[]);
	void InitLights();

	// Update Loop
	void Update();
	// Draw Screen
	void Display();
	// Draw a String
	void DrawString(const char* text, Vector3* position, Color* color);

	void Keyboard(unsigned char key, int x, int y, bool keyUp);

	bool InRange(float comparison, float bound1, float bound2);
};

