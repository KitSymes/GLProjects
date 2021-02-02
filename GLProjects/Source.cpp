#include "Source.h"

int main(int argc, char* argv[])
{
	Source* window = new Source(argc, argv);

	return 0;
}

Vertex Source::vertices[] = { 1, 1, 1, -1, 1, 1, -1, -1, 1, -1, -1, 1, 1, -1, 1, 1, 1, 1, 1, 1, 1, 1, -1, 1, 1, -1, -1, 1, -1, -1, 1, 1, -1, 1, 1, 1, 1, 1, 1, 1, 1, -1, -1, 1, -1, -1, 1, -1, -1, 1, 1, 1, 1, 1, -1, 1, 1, -1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, -1, 1, 1, -1, -1, -1, 1, -1, -1, 1, -1, 1, 1, -1, 1, -1, -1, 1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, 1, -1, -1, 1, -1, 1, 1, -1, 1, -1, -1 };
Colour Source::colours[] = { 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1 };

Vertex Source::indexedVertices[] = { 1, 1, 1, -1, 1, 1, -1, -1, 1, 1, -1, 1, 1, -1, -1, 1, 1, -1, -1, 1, -1, -1, -1, -1 };
Colour Source::indexedColors[] = { 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0 };
GLushort Source::indices[] = {0, 1, 2, 2, 3, 0, 0, 3, 4, 4, 5, 0, 0, 5, 6, 6, 1, 0, 1, 6, 7, 7, 2, 1, 7, 4, 3, 3, 2, 7, 4, 7, 6, 6, 5, 4};

Source::Source(int argc, char* argv[])
{
	rotation = 0.0f;
	camera = new Camera();
	camera->eye.x = 5.0f;
	camera->eye.y = 5.0f;
	camera->eye.z = -5.0f;
	camera->center.x = 0.0f;
	camera->center.y = 0.0f;
	camera->center.z = 0.0f;
	camera->up.x = 0.0f;
	camera->up.y = 1.0f;
	camera->up.z = 0.0f;

	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	glutCreateWindow("GL Project");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESH_RATE, GLUTCallbacks::Timer, REFRESH_RATE);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Set the viewport to encase the entire window
	glViewport(0, 0, 800, 800);
	// Set the correct perspective
	// FoV, Aspect Ratio, Near Clipping, Far Clipping
	gluPerspective(45, 1, 0, 1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glutMainLoop();
}

Source::~Source(void)
{
	delete camera;
}

void Source::Update()
{
	glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z,
		camera->center.x, camera->center.y, camera->center.z,
		camera->up.x, camera->up.y, camera->up.z);

	if (rotation >= 360.0f)
		rotation = 0.0f;

	glutPostRedisplay();
}

void Source::Display()
{
	glClear(GL_COLOR_BUFFER_BIT); // Clears frame

	//DrawCube();
	//DrawCubeArray();
	DrawIndexedCube();

	/*glPushMatrix();
	glTranslatef(-0.5f, 0.5f, -2.0f);
	glRotatef(rotation, 0.0f, 0.0f, -1.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
	DrawHex(5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5f, 0.5f, -2.0f);
	glRotatef(-rotation, 0.0f, 0.0f, -1.0f);
	glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	DrawHex(2.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5f, 0.5f, -2.0f);
	glRotatef(-rotation, 0.0f, 0.0f, -1.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
	DrawHex(5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5f, 0.5f, -2.0f);
	glRotatef(rotation, 0.0f, 0.0f, -1.0f);
	glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	DrawHex(2.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -2.0f);
	glRotatef(rotation, 1.0f, 0.0f, 0.0f);
	glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	DrawPolygon();
	glPopMatrix();*/

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

void Source::DrawCube()
{
	glBegin(GL_TRIANGLES);
	{
		glColor3f(1, 1, 1);
		glVertex3f(1, 1, 1);
		glColor3f(1, 1, 0);
		glVertex3f(-1, 1, 1);
		glColor3f(1, 0, 0);
		glVertex3f(-1, -1, 1);

		glColor3f(1, 0, 0);
		glVertex3f(-1, -1, 1);
		glColor3f(1, 0, 1);
		glVertex3f(1, -1, 1);
		glColor3f(1, 1, 1);
		glVertex3f(1, 1, 1);
	}

	{
		glColor3f(1, 1, 1);
		glVertex3f(1, 1, 1);
		glColor3f(1, 0, 1);
		glVertex3f(1, -1, 1);
		glColor3f(0, 0, 1);
		glVertex3f(1, -1, -1);

		glColor3f(0, 0, 1);
		glVertex3f(1, -1, -1);
		glColor3f(0, 1, 1);
		glVertex3f(1, 1, -1);
		glColor3f(1, 1, 1);
		glVertex3f(1, 1, 1);
	}

	{
		glColor3f(1, 1, 1);
		glVertex3f(1, 1, 1);
		glColor3f(0, 1, 1);
		glVertex3f(1, 1, -1);
		glColor3f(0, 1, 0);
		glVertex3f(-1, 1, -1);

		glColor3f(0, 1, 0);
		glVertex3f(-1, 1, -1);
		glColor3f(1, 1, 0);
		glVertex3f(-1, 1, 1);
		glColor3f(1, 1, 1);
		glVertex3f(1, 1, 1);
	}

	{
		glColor3f(1, 1, 0);
		glVertex3f(-1, 1, 1);
		glColor3f(0, 1, 0);
		glVertex3f(-1, 1, -1);
		glColor3f(0, 0, 0);
		glVertex3f(-1, -1, -1);

		glColor3f(0, 0, 0);
		glVertex3f(-1, -1, -1);
		glColor3f(1, 0, 0);
		glVertex3f(-1, -1, 1);
		glColor3f(1, 1, 0);
		glVertex3f(-1, 1, 1);
	}

	{
		glColor3f(0, 0, 0);
		glVertex3f(-1, -1, -1);
		glColor3f(0, 0, 1);
		glVertex3f(1, -1, -1);
		glColor3f(1, 0, 1);
		glVertex3f(1, -1, 1);

		glColor3f(1, 0, 1);
		glVertex3f(1, -1, 1);
		glColor3f(1, 0, 0);
		glVertex3f(-1, -1, 1);
		glColor3f(0, 0, 0);
		glVertex3f(-1, -1, -1);
	}

	{
		glColor3f(0, 0, 1);
		glVertex3f(1, -1, -1);
		glColor3f(0, 0, 0);
		glVertex3f(-1, -1, -1);
		glColor3f(0, 1, 0);
		glVertex3f(-1, 1, -1);

		glColor3f(0, 1, 0);
		glVertex3f(-1, 1, -1);
		glColor3f(0, 1, 1);
		glVertex3f(1, 1, -1);
		glColor3f(0, 0, 1);
		glVertex3f(1, -1, -1);
	}


	glEnd();
}

void Source::DrawCubeArray()
{
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 36; i++)
	{
		glColor3fv(&colours[i].r);
		glVertex3fv(&vertices[i].x);
	}
	glEnd();
	glPopMatrix();
}

void Source::DrawIndexedCube()
{
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 36; i++)
	{
		glColor3fv(&indexedColors[indices[i]].r);
		glVertex3fv(&indexedVertices[indices[i]].x);
	}
	glEnd();
	glPopMatrix();
}

void Source::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'q')
		rotation += 2.0f;
	else if (key == 'e')
		rotation -= 2.0f;

	if (key == 'w')
		camera->eye.x += 0.1;
	if (key == 's')
		camera->eye.x -= 0.1;
	if (key == 'a')
		camera->eye.z += 0.1;
	if (key == 'd')
		camera->eye.z -= 0.1;
}
