#pragma once
#ifndef _STRUCTURES_H
#define _STRUCTURES_H
#include <iostream>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTCallbacks.h"
#include "Texture2D.h"

struct Vector3
{
	float x, y, z;

	Vector3()
	{

	}

	Vector3(GLfloat x, GLfloat y, GLfloat z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3 operator +(Vector3 arg)
	{
		return Vector3(this->x + arg.x, this->y + arg.y, this->z + arg.z);
	}

	void operator +=(Vector3 arg)
	{
		this->x += arg.x;
		this->y += arg.y;
		this->z += arg.z;
	}

	Vector3 operator -(Vector3 arg)
	{
		return Vector3(this->x - arg.x, this->y - arg.y, this->z - arg.z);
	}

	void operator -=(Vector3 arg)
	{
		this->x -= arg.x;
		this->y -= arg.y;
		this->z -= arg.z;
	}

	Vector3 operator -()
	{
		return Vector3(-this->x, -this->y, -this->z);
	}

	Vector3 operator *(float arg)
	{
		return Vector3(this->x * arg, this->y * arg, this->z * arg);
	}

	Vector3 operator /(float arg)
	{
		return Vector3(this->x / arg, this->y / arg, this->z / arg);
	}
};

std::ostream& operator<<(std::ostream& os, const Vector3& obj);

struct Vector4
{
	float x, y, z, w;
};

struct Camera
{
	Vector3 eyePos, lookingAtPos, up;
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
#endif
