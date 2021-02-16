#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "SceneObject.h"

class Pyramid : public SceneObject
{
private:
	GLfloat _rotationX = 0.0f, _rotationY = 0.0f, _rotationZ = 0.0f;
	GLfloat _x, _y, _z;
public:
	Pyramid(Mesh* mesh, GLfloat x, GLfloat y, GLfloat z);
	~Pyramid();

	void SetRotation(GLfloat rotationX, GLfloat rotationY, GLfloat rotationZ);
	void Draw();
	void Update();
};



