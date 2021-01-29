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

	void Timer(int preferredRefresh)
	{
		int updateTime = glutGet(GLUT_ELAPSED_TIME);
		gl->Update();

		updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
		glutTimerFunc(preferredRefresh - updateTime, GLUTCallbacks::Timer, preferredRefresh);
	}

	void Keyboard(unsigned char key, int x, int y)
	{
		gl->Keyboard(key, x, y);
	}
}