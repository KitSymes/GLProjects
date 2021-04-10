#pragma once

#include "Structures.h"

namespace MeshLoader
{
	Mesh* Load(char* path, char* texPath, int width, int height);
	Mesh* LoadObj(char* path, char* texPath);
};

