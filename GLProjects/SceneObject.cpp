#include "SceneObject.h"
#include <corecrt_math.h>
#include <corecrt_math_defines.h>

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

void SceneObject::Move(Vector3 velo)
{
	_x += velo.x;
	_y += velo.y;
	_z += velo.z;
}

Vector3 SceneObject::GetForward()
{
	return Vector3(
		cos(GetRotation().x * M_PI / 180) * sin(GetRotation().y * M_PI / 180),
		sin(GetRotation().x * M_PI / 180) * sin(GetRotation().y * M_PI / 180),
		cos(GetRotation().y * M_PI / 180)
	);
}

Vector3 SceneObject::GetRight()
{
	return Vector3(
		cos(GetRotation().x * M_PI / 180) * sin((GetRotation().y + 90) * M_PI / 180),
		sin(GetRotation().x * M_PI / 180) * sin((GetRotation().y + 90) * M_PI / 180),
		cos((GetRotation().y + 90) * M_PI / 180)
	);
}

Vector3 SceneObject::GetUp()
{
	return Vector3(0, 1, 0);
}
