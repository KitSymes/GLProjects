#pragma once
#include<Windows.h>
#include<gl/GL.h>
#include<gl/GLU.h>
#include"GL\freeglut.h"
#include"GLUTCallbacks.h"
class Source
{
public:
	Source(int argc, char* argv[]);
	~Source(void);

	void Display();
	void DrawPolygon();
	void DrawHex(float x, float y, float scale);
};

