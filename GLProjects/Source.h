#pragma once
#include<Windows.h>
#include<gl/GL.h>
#include<gl/GLU.h>
#include"GL\freeglut.h"
#include"GLUTCallbacks.h"
#define REFRESH_RATE 16

struct Vector3
{
	float x, y, z;
};

struct Camera
{
	Vector3 eye, center, up;
};

struct Colour
{
	GLfloat r, g, b;
};

struct Vertex
{
	GLfloat x, y, z;
};

class Source
{
private:
	float rotation;
	Camera* camera;
	static Vertex vertices[];
	static Colour colours[];
	static Vertex indexedVertices[];
	static Colour indexedColors[];
	static GLushort indices[];
public:
	// Constructor
	Source(int argc, char* argv[]);
	// Deconstructor
	~Source(void);

	// Update Loop
	void Update();
	// Draw Screen
	void Display();
	// Draw Mouth Poly
	void DrawPolygon();
	// Draw a Regular Hexagon at 0,0 with specified scale
	void DrawHex(float scale);

	void DrawCube();
	void DrawCubeArray();
	void DrawIndexedCube();

	void Keyboard(unsigned char key, int x, int y);
};

