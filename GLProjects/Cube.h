#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "SceneObject.h"

class Cube : public SceneObject
{
private:
	GLfloat _rotationX = 0.0f, _rotationY = 0.0f, _rotationZ = 0.0f;
	GLfloat _x, _y, _z;
	Material* _material;
public:
	Cube(Mesh* mesh, GLfloat x, GLfloat y, GLfloat z);
	~Cube();

	void SetRotation(GLfloat rotationX, GLfloat rotationY, GLfloat rotationZ);
	void Draw();
	void Update();
};

