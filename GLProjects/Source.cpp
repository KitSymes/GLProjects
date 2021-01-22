#include "Source.h"

int main(int argc, char* argv[])
{
	Source* window = new Source(argc, argv);

	return 0;
}

Source::Source(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutCreateWindow("Test");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutMainLoop();
}

Source::~Source(void)
{

}

void Source::Display()
{
	glClear(GL_COLOR_BUFFER_BIT); // Clears frame

	glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
	DrawHex(-0.5, 0 + 0.5, 5);
	glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	DrawHex(-0.5, 0 + 0.5, 2.5);
	glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
	DrawHex(0.5, 0 + 0.5, 5);
	glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	DrawHex(0.5, 0 + 0.5, 2.5);

	glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON); // Starts Drawing Polygon
	{
		glVertex2f(-0.6, 0.2);
		glColor4f(0.9f, 1.0f, 1.0f, 0.0f);
		glVertex2f(-0.4, 0.2);
		glColor4f(0.8f, 1.0f, 1.0f, 0.0f);
		glVertex2f(-0.4, 0);
		glColor4f(0.7f, 1.0f, 1.0f, 0.0f);
		glVertex2f(-0.2, -0.25);
		glColor4f(0.6f, 1.0f, 1.0f, 0.0f);
		glVertex2f(0.2, -0.25);
		glColor4f(0.5f, 1.0f, 1.0f, 0.0f);
		glVertex2f(0.4, 0);
		glColor4f(0.4f, 1.0f, 1.0f, 0.0f);
		glVertex2f(0.4, 0.2);
		glColor4f(0.3f, 1.0f, 1.0f, 0.0f);
		glVertex2f(0.6, 0.2);
		glColor4f(0.2f, 1.0f, 1.0f, 0.0f);
		glVertex2f(0.6, -0.2);
		glColor4f(0.1f, 1.0f, 1.0f, 0.0f);
		glVertex2f(0.2, -0.45);
		glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
		glVertex2f(-0.2, -0.45);
		glColor4f(0.5f, 0.9f, 1.0f, 0.0f);
		glVertex2f(-0.6, -0.2);
		//glVertex2f(0.4, 0.2);
	}
	glEnd(); // Stops

	glFlush(); // Sends to Graphics Card or something
}

void Source::DrawPolygon()
{
	glBegin(GL_POLYGON); // Starts Drawing Polygon
	{
		glVertex2f(0, 0.75);
		glVertex2f(0.75, 0);
		glVertex2f(0.5, -0.5);
	}
	glEnd(); // Stops
}

void Source::DrawHex(float x, float y, float scale)
{
	glBegin(GL_POLYGON);
	{
		glVertex2f(x - (0.025 * scale), y + (0.015 * scale));
		glVertex2f(x, y + (0.025 * scale));
		glVertex2f(x + (0.025 * scale), y + (0.015 * scale));
		glVertex2f(x + (0.025 * scale), y - (0.015 * scale));
		glVertex2f(x, y - (0.025 * scale));
		glVertex2f(x - (0.025 * scale), y - (0.015 * scale));
	}
	glEnd();
}