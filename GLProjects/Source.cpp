#include "Source.h"

int main(int argc, char* argv[])
{
	Source* window = new Source(argc, argv);

	return 0;
}

Source::Source(int argc, char* argv[])
{
	rotation = 0.0f;

	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutCreateWindow("GL Project");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESH_RATE, GLUTCallbacks::Timer, REFRESH_RATE);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutMainLoop();
}

Source::~Source(void)
{

}

void Source::Update()
{
	if (rotation >= 360.0f)
		rotation = 0.0f;

	glutPostRedisplay();
}

void Source::Display()
{
	glClear(GL_COLOR_BUFFER_BIT); // Clears frame

	glPushMatrix();
	glTranslatef(-0.5f, 0.5f, 0.0f);
	glRotatef(rotation, 0.0f, 0.0f, -1.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
	DrawHex(5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5f, 0.5f, 0.0f);
	glRotatef(-rotation, 0.0f, 0.0f, -1.0f);
	glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	DrawHex(2.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 0.5, 0);
	glRotatef(-rotation, 0.0f, 0.0f, -1.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
	DrawHex(5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5f, 0.5f, 0.0f);
	glRotatef(rotation, 0.0f, 0.0f, -1.0f);
	glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	DrawHex(2.5);
	glPopMatrix();

	DrawPolygon();

	glFlush(); // Sends to Graphics Card or something
	glutSwapBuffers();
}

void Source::DrawPolygon()
{
	glBegin(GL_POLYGON); // Starts Drawing Polygon
	{
		glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
		glVertex2f(-0.6, 0.2);
		/*glColor4f(0.9f, 1.0f, 1.0f, 0.0f);
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
		glVertex2f(0.4, 0.2);*/
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
	}
	glEnd(); // Stops
}

void Source::DrawHex(float scale)
{
	scale /= 2;
	glBegin(GL_POLYGON);
	{
		glVertex2f(-(0.05 * scale), (0.03 * scale));
		glVertex2f(0, (0.06 * scale));
		glVertex2f((0.05 * scale), (0.03 * scale));
		glVertex2f((0.05 * scale), -(0.03 * scale));
		glVertex2f(0, -(0.06 * scale));
		glVertex2f(-(0.05 * scale), -(0.03 * scale));
	}
	glEnd();
}

void Source::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'd')
		rotation += 2.0f;
	else if (key == 'a')
		rotation -= 2.0f;
}
