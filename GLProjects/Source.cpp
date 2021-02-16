#include "Source.h"

int main(int argc, char* argv[])
{
	Source* window = new Source(argc, argv);

	return 0;
}

Source::Source(int argc, char* argv[])
{
	srand(time(NULL));

	InitGL(argc, argv);
	InitObjects();

	glutMainLoop();
}

Source::~Source(void)
{
	delete camera;
	delete objects[0];
	delete[] objects;
}

void Source::InitObjects()
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

	Mesh* cubeMesh = MeshLoader::Load((char*)"cube.txt");
	Mesh* pyramidMesh = MeshLoader::Load((char*)"pyramid.txt");

	for (int i = 0; i < 25; i++)
		objects[i] = new Cube(cubeMesh, rand() % 25 - 12.5f, rand() % 25 - 12.5f, rand() % 25 - 12.5f);
	for (int i = 25; i < 50; i++)
		objects[i] = new Pyramid(pyramidMesh, rand() % 25 - 12.5f, rand() % 25 - 12.5f, rand() % 25 - 12.5f);
}

void Source::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
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
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clears frame

	for (int i = 0; i < 50; i++)
		objects[i]->Draw();

	//DrawCube();
	//DrawCubeArray();
	//DrawIndexedCube();

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
		glVertex2f(-0.6f, 0.2f);
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
		glVertex2f(0.6f, 0.2f);
		glColor4f(0.2f, 1.0f, 1.0f, 0.0f);
		glVertex2f(0.6f, -0.2f);
		glColor4f(0.1f, 1.0f, 1.0f, 0.0f);
		glVertex2f(0.2f, -0.45f);
		glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
		glVertex2f(-0.2f, -0.45f);
		glColor4f(0.5f, 0.9f, 1.0f, 0.0f);
		glVertex2f(-0.6f, -0.2f);
	}
	glEnd(); // Stops
}

void Source::DrawHex(float scale)
{
	scale /= 2;
	glBegin(GL_POLYGON);
	{
		glVertex2f(-(0.05f * scale), (0.03f * scale));
		glVertex2f(0, (0.06f * scale));
		glVertex2f((0.05f * scale), (0.03f * scale));
		glVertex2f((0.05f * scale), -(0.03f * scale));
		glVertex2f(0, -(0.06f * scale));
		glVertex2f(-(0.05f * scale), -(0.03f * scale));
	}
	glEnd();
}

void Source::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'q')
		rotation += 2.0f;
	else if (key == 'e')
		rotation -= 2.0f;

	if (key == 'w')
		camera->eye.x += 0.1f;
	if (key == 's')
		camera->eye.x -= 0.1f;
	if (key == 'a')
		camera->eye.z += 0.1f;
	if (key == 'd')
		camera->eye.z -= 0.1f;
}
