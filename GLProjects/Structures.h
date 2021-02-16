#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTCallbacks.h"

struct Vector3
{
	float x, y, z;
};

struct Camera
{
	Vector3 eye, center, up;
};

struct Color
{
	GLfloat r, g, b;
};

struct Vertex
{
	GLfloat x, y, z;
};

struct Mesh
{
	Vertex* Vertices;
	Color* Colors;
	GLushort* Indices;
	int VertexCount, ColorCount, IndexCount;
	~Mesh()
	{
		if (Vertices != nullptr)
		{
			delete[] Vertices;
			Vertices = nullptr;
		}
		if (Colors != nullptr)
		{
			delete[] Colors;
			Colors = nullptr;
		}
		if (Indices != nullptr)
		{
			delete[] Indices;
			Indices = nullptr;
		}
	}
};