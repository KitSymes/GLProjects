#pragma once
#include "Structures.h"
#include "Texture2D.h"

class SceneObject
{
protected:
	Mesh* _mesh;
public:
	SceneObject(Mesh* mesh);
	~SceneObject();

	virtual void Update() = 0;
	virtual void Draw() = 0;
};
