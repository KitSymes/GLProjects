#include "Structures.h"

std::ostream& operator<<(std::ostream& os, const Vector3& obj)
{
	os << "(" << obj.x << "," << obj.y << "," << obj.z << ")";
	return os;
}