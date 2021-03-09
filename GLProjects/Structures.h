#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTCallbacks.h"
#include "Texture2D.h"

struct Vector3
{
	float x, y, z;
};

struct Vector4
{
	float w, x, y, z;
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

struct TexCoord
{
	GLfloat u, v;
};

struct Lighting
{
	Vector4 Ambient, Diffuse, Specular;
};

struct Material
{
	Vector4 Ambient, Diffuse, Specular;
	GLfloat Shininess;
};

struct Mesh
{
	Vertex* Vertices;
	GLushort* Indices;
	TexCoord* TexCoords;
	Vector3* Normals;
	Texture2D* _texture;
	int VertexCount, ColorCount, IndexCount, TexCoordCount, NormalCount;

	~Mesh()
	{
		if (Vertices != nullptr)
		{
			delete[] Vertices;
			Vertices = nullptr;
		}
		if (Indices != nullptr)
		{
			delete[] Indices;
			Indices = nullptr;
		}
		if (TexCoords != nullptr) {
			delete[] TexCoords;
			TexCoords = nullptr;
		}
		if (Normals != nullptr) {
			delete[] Normals;
			Normals = nullptr;
		}
		delete _texture;
	}
};