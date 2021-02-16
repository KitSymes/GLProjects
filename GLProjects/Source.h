#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTCallbacks.h"
#include "Cube.h"
#include "Pyramid.h"
#include <time.h>
#include "MeshLoader.h"
#define REFRESH_RATE 16

class Source
{
private:
	float rotation;
	Camera* camera;
	SceneObject* objects[50];
public:
	// Constructor
	Source(int argc, char* argv[]);
	// Deconstructor
	~Source(void);

	void InitObjects();
	void InitGL(int argc, char* argv[]);

	// Update Loop
	void Update();
	// Draw Screen
	void Display();
	// Draw Mouth Poly
	void DrawPolygon();
	// Draw a Regular Hexagon at 0,0 with specified scale
	void DrawHex(float scale);

	void Keyboard(unsigned char key, int x, int y);
};

