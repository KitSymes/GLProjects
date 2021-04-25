#pragma once
class Source;

namespace GLUTCallbacks
{
	void Init(Source* gl);
	void Display();
	void Timer(int preferredRefresh);
	void Keyboard(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
};

