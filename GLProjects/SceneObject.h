#pragma once
#include "Structures.h"
#include "Texture2D.h"
#include "MeshLoader.h"

class SceneObject
{
protected:
	Mesh* _mesh;
	GLfloat _rotationX = 0.0f, _rotationY = 0.0f, _rotationZ = 0.0f;
	GLfloat _x, _y, _z;
public:
	SceneObject();
	SceneObject(Mesh* mesh);
	~SceneObject();

	virtual void Update() = 0;
	virtual void Draw() = 0;

	void SetPosition(GLfloat positionX, GLfloat positionY, GLfloat positionZ);
	void SetRotation(GLfloat rotationX, GLfloat rotationY, GLfloat rotationZ);
};
