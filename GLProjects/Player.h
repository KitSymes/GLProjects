#pragma once
#ifndef _Player_H
#define _Player_H
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "SceneObject.h"
class Player : public SceneObject
{
private:
	Material* _material;
public:
	Vector3 _velocity;

	Player(GLfloat x, GLfloat y, GLfloat z);
	~Player();

	void Draw();
	void Update();
};
#endif
