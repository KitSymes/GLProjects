#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "SceneObject.h"
class Player : public SceneObject
{
private:
	Mesh* _mesh;
	Material* _material;
public:
	Player(GLfloat x, GLfloat y, GLfloat z);
	~Player();

	void Draw();
	void Update();
};

