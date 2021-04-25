#pragma once
#ifndef _SceneObject_H
#define _SceneObject_H
#include "Structures.h"
#include "Texture2D.h"
#include "MeshLoader.h"
class SceneObject
{
protected:
	Mesh* _mesh;
	GLfloat _rotationX = 0.0f, _rotationY = 0.0f, _rotationZ = 0.0f;
	GLfloat _x, _y, _z;

	SceneObject* parent;
	SceneObject* child;
	SceneObject* sibling;
public:
	SceneObject();
	SceneObject(Mesh* mesh);
	virtual ~SceneObject();

	virtual void Update() = 0;
	virtual void Draw() = 0;

	Vector3 GetPosition();
	void SetPosition(GLfloat positionX, GLfloat positionY, GLfloat positionZ);

	Vector3 GetRotation();
	void SetRotation(GLfloat rotationX, GLfloat rotationY, GLfloat rotationZ);

	void Move(Vector3 velo);
	Vector3 GetForward();
	Vector3 GetRight();
	Vector3 GetUp();
};
#endif
