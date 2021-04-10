#include "SceneObject.h"

SceneObject::SceneObject()
{
}

SceneObject::SceneObject(Mesh* mesh)
{
	_mesh = mesh;
}

SceneObject::~SceneObject()
{
	delete _mesh;
}

void SceneObject::SetPosition(GLfloat positionX, GLfloat positionY, GLfloat positionZ)
{
	_x = positionX;
	_y = positionY;
	_z = positionZ;
}

void SceneObject::SetRotation(GLfloat rotationX, GLfloat rotationY, GLfloat rotationZ)
{
	_rotationX = rotationX;
	_rotationY = rotationY;
	_rotationZ = rotationZ;
}

