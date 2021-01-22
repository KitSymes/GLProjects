#include "GLUTCallbacks.h"
#include "Source.h"

namespace GLUTCallbacks
{
	namespace
	{
		Source* gl = nullptr;
	}

	void Init(Source* glIn)
	{
		gl = glIn;
	}

	void Display()
	{
		if (gl != nullptr)
		{
			gl->Display();
		}
	}
}