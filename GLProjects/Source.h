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
	float rotation;
	Camera* camera;
	SceneObject* objects[75];
	Vector4* _lightPosition;
	Lighting* _lightData;

	// Scene Objects
	SceneObject* _root;
	Checkpoint* _checkpoints[10];
	Player* _player;

	int _player_checkpoint = 0;
	int _player_lap = 1;
	bool _player_forwards = false;
	bool _player_backwards = false;
	bool _player_left = false;
	bool _player_right = false;
	bool _player_up = false;
	bool _player_down = false;
public:
	// Constructor
	Source(int argc, char* argv[]);
	// Deconstructor
	~Source(void);

	void InitObjects();
	void InitGL(int argc, char* argv[]);
	void InitLights();

	// Update Loop
	void Update();
	// Draw Screen
	void Display();
	// Draw Mouth Poly
	void DrawPolygon();
	// Draw a Regular Hexagon at 0,0 with specified scale
	void DrawHex(float scale);
	// Draw a String
	void DrawString(const char* text, Vector3* position, Color* color);

	void Keyboard(unsigned char key, int x, int y, bool keyUp);
};

