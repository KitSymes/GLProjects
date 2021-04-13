#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "SceneObject.h"
class GenericObject : public SceneObject
{
private:
	Material* _material;
public:
	GenericObject(Mesh* mesh, GLfloat x, GLfloat y, GLfloat z);
	~GenericObject();

	void Draw();
	void Update();
};

