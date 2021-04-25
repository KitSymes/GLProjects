#pragma once
#ifndef _Checkpoint_H
#define _Checkpoint_H
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "SceneObject.h"
class Checkpoint : public SceneObject
{
private:
	Material* _material;

	Texture2D* _inUse;
	Texture2D* _textureWrong;
	Texture2D* _textureNext;
	Texture2D* _textureDone;
public:
	Checkpoint(Mesh* mesh, Texture2D* wrong, Texture2D* next, Texture2D* done, GLfloat x, GLfloat y, GLfloat z);
	~Checkpoint();

	void SetWrong();
	void SetNext();
	void SetDone();
	void DeleteTextures();

	void Draw();
	void Update();
};
#endif
