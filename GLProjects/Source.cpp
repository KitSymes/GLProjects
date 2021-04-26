#include "Source.h"
#define windowWidth 800
#define windowHeight 800

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
	InitLights();

	glutMainLoop();
}

Source::~Source(void)
{
	delete camera;
	delete _player;
	delete _root;
	_checkpoints[0]->DeleteTextures();
	for (int i = 0; i < 10; i++)
		delete _checkpoints[i];
	delete[] _checkpoints;
	delete _lightPosition;
	delete _lightData;
}

void Source::InitObjects()
{
	camera = new Camera();
	camera->eyePos.x = 1.0f;
	camera->eyePos.y = -10.0f;
	camera->eyePos.z = 0.0f;
	camera->lookingAtPos.x = 0.0f;
	camera->lookingAtPos.y = 1.0f;
	camera->lookingAtPos.z = 0.0f;
	camera->up.x = 0.0f;
	camera->up.y = 1.0f;
	camera->up.z = 0.0f;

	Mesh* rootMesh = MeshLoader::LoadObj((char*)"Resources/Models/terrain.obj");
	rootMesh->_texture->LoadBitMap((char*)"Resources/Textures/Terrain.bmp");
	_root = new GenericObject(rootMesh, 0, 0, 0);

	Mesh* checkpointMesh = MeshLoader::LoadObj((char*)"Resources/Models/checkpoint.obj");
	Texture2D* checkpointWrong = new Texture2D();
	checkpointWrong->LoadBitMap((char*)"Resources/Textures/CheckpointWrong.bmp");
	Texture2D* checkpointNext = new Texture2D();
	checkpointNext->LoadBitMap((char*)"Resources/Textures/CheckpointNext.bmp");
	Texture2D* checkpointDone = new Texture2D();
	checkpointDone->LoadBitMap((char*)"Resources/Textures/CheckpointDone.bmp");

	for (int i = 0; i < 10; i++)
		_checkpoints[i] = new Checkpoint(checkpointMesh, checkpointWrong, checkpointNext, checkpointDone, 0, 0, 0);
	_checkpoints[0]->SetPosition(-24, 17, 78);
	_checkpoints[0]->SetRotation(0, -45, 0);
	_checkpoints[1]->SetPosition(-256, 50, 145);
	_checkpoints[1]->SetRotation(0, -90, 0);
	_checkpoints[2]->SetPosition(-467, 73, 141);
	_checkpoints[2]->SetRotation(10, -100, 10);
	_checkpoints[3]->SetPosition(-573, 100, 135);
	_checkpoints[3]->SetRotation(0, -80, 0);
	_checkpoints[4]->SetPosition(-760, 94, 238);
	_checkpoints[4]->SetRotation(0, -200, 0);
	_checkpoints[4]->SetPosition(-871, 66, 252);
	_checkpoints[4]->SetRotation(0, 20, 0);
	_checkpoints[5]->SetPosition(-696, 58, 389);
	_checkpoints[5]->SetRotation(0, 90, 0);
	_checkpoints[6]->SetPosition(-270, 60, 327);
	_checkpoints[6]->SetRotation(197, -13, 185);
	_checkpoints[7]->SetPosition(-332, 206, 33);
	_checkpoints[7]->SetRotation(0, 180, 0);
	_checkpoints[8]->SetPosition(-347, 198, -128);
	_checkpoints[8]->SetRotation(0, 100, 0);
	_checkpoints[9]->SetPosition(-35, 38, -171);
	_checkpoints[9]->SetRotation(0, 30, 0);

	_player = new Player(0, 0, 0);

	start_time = clock();
}

void Source::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("GL Project");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESH_RATE, GLUTCallbacks::Timer, REFRESH_RATE);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutKeyboardUpFunc(GLUTCallbacks::KeyboardUp);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Set the viewport to encase the entire window
	glViewport(0, 0, 800, 800);
	// Set the correct perspective
	// FoV, Aspect Ratio, Near Clipping, Far Clipping
	gluPerspective(45, 1, 0.01f, 1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_ALWAYS); //
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void Source::InitLights()
{
	_lightPosition = new Vector4();
	_lightPosition->x = 0.0;
	_lightPosition->y = 0.0;
	_lightPosition->z = 1.0;
	_lightPosition->w = 0.0;

	_lightData = new Lighting();
	_lightData->Ambient.x = 1.0;
	_lightData->Ambient.y = 1.0;
	_lightData->Ambient.z = 1.0;
	_lightData->Ambient.w = 1;
	_lightData->Diffuse.x = 0.8;
	_lightData->Diffuse.y = 0.8;
	_lightData->Diffuse.z = 0.8;
	_lightData->Diffuse.w = 1.0;
	_lightData->Specular.x = 0.2;
	_lightData->Specular.y = 0.2;
	_lightData->Specular.z = 0.2;
	_lightData->Specular.w = 1.0;
}

int i = 0;

void Source::Update()
{
	glLoadIdentity();
	i++;
	i = i % 360;

	if (0 <= _player_lap && _player_lap < 4)
	{
		float multi = 0.01f;

		if (_player_forwards)
			_player->_velocity += _player->GetForward() * multi;
		if (_player_backwards)
			_player->_velocity -= _player->GetForward() * multi;
		if (_player_left)
			_player->_velocity += _player->GetRight() * multi;
		if (_player_right)
			_player->_velocity -= _player->GetRight() * multi;
		if (_player_up)
			_player->_velocity += _player->GetUp() * multi;
		if (_player_down)
			_player->_velocity -= _player->GetUp() * multi;

		if (_player_rotateLeft)
			_player->SetRotation(_player->GetRotation().x, _player->GetRotation().y + 2.0f, _player->GetRotation().z);
		if (_player_rotateRight)
			_player->SetRotation(_player->GetRotation().x, _player->GetRotation().y - 2.0f, _player->GetRotation().z);


		if (_player->GetPosition().distanceSquared(_checkpoints[_player_checkpoint]->GetPosition()) <= 200)
		{
			Vector3 p4 = _checkpoints[_player_checkpoint]->GetPosition() + _checkpoints[_player_checkpoint]->GetRight() * -6 + _checkpoints[_player_checkpoint]->GetUp() * -7 + -_checkpoints[_player_checkpoint]->GetForward();
			Vector3 p1 = _checkpoints[_player_checkpoint]->GetPosition() + _checkpoints[_player_checkpoint]->GetRight() * 6 + _checkpoints[_player_checkpoint]->GetUp() * -7 + -_checkpoints[_player_checkpoint]->GetForward();
			Vector3 p5 = _checkpoints[_player_checkpoint]->GetPosition() + _checkpoints[_player_checkpoint]->GetRight() * 6 + _checkpoints[_player_checkpoint]->GetUp() * 5 + -_checkpoints[_player_checkpoint]->GetForward();
			Vector3 p2 = _checkpoints[_player_checkpoint]->GetPosition() + _checkpoints[_player_checkpoint]->GetRight() * 6 + _checkpoints[_player_checkpoint]->GetUp() * -7 + _checkpoints[_player_checkpoint]->GetForward();

			Vector3 u = p1 - p2;
			Vector3 v = p1 - p4;
			Vector3 w = p1 - p5;

			float ux = u.dotProduct(_player->GetPosition());
			float up1 = u.dotProduct(p1);
			float up2 = u.dotProduct(p2);

			float vx = v.dotProduct(_player->GetPosition());
			float vp1 = v.dotProduct(p1);
			float vp4 = v.dotProduct(p4);

			float wx = w.dotProduct(_player->GetPosition());
			float wp1 = w.dotProduct(p1);
			float wp5 = w.dotProduct(p5);

			if (InRange(ux, up1, up2) &&
				InRange(vx, vp1, vp4) &&
				InRange(wx, wp1, wp5))
			{
				_player_checkpoint++;
				if (_player_checkpoint >= 10)
				{
					_player_checkpoint = 0;
					_player_lap++;
				}
			}
		}
	}
	Vector3 eyePosBackup = camera->eyePos;
	camera->eyePos = _player->GetPosition();
	camera->eyePos.y += 2.5;
	Vector3 dir = _player->GetForward() * 8;
	camera->eyePos.x -= dir.x;
	camera->eyePos.y -= dir.y;
	camera->eyePos.z -= dir.z;
	camera->lookingAtPos.x = camera->eyePos.x + cos(_player->GetRotation().x * M_PI / 180) * sin(_player->GetRotation().y * M_PI / 180);
	camera->lookingAtPos.y = camera->eyePos.y + sin(_player->GetRotation().x * M_PI / 180) * sin(_player->GetRotation().y * M_PI / 180) - 0.2;
	camera->lookingAtPos.z = camera->eyePos.z + cos(_player->GetRotation().y * M_PI / 180);
	if (_player_lap == 4)
		camera->eyePos = eyePosBackup;

	gluLookAt(camera->eyePos.x, camera->eyePos.y, camera->eyePos.z,
		camera->lookingAtPos.x, camera->lookingAtPos.y, camera->lookingAtPos.z,
		camera->up.x, camera->up.y, camera->up.z);

	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->Specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));

	_player->Update();

	glutPostRedisplay();
}

void Source::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clears frame

	/*for (int i = 0; i < 75; i++)
		if (objects[i] != nullptr)
			objects[i]->Draw();*/
			//objects[0]->Draw();

	_root->Draw();
	for (int i = 0; i < 10; i++)
	{
		if (i < _player_checkpoint)
			_checkpoints[i]->SetDone();
		else if (i == _player_checkpoint)
			_checkpoints[i]->SetNext();
		else
			_checkpoints[i]->SetWrong();
		_checkpoints[i]->Draw();
	}
	_player->Draw();

	Vector3 position = { 0.0f, 780.0f, 0.0f };
	Color colour = { 0.0f, 1.0f, 0.0f };
	std::string checkpoint = "Checkpoint: ";
	DrawString(checkpoint.append(std::to_string(_player_checkpoint)).append(" / 10").c_str(), &position, &colour);
	position = { 0.0f, 750.0f, 0.0f };
	std::string lap = "Lap: ";
	DrawString(lap.append(std::to_string(_player_lap)).append(" / 3").c_str(), &position, &colour);
	position = { 0.0f, 720.0f, 0.0f };
	std::string time = "Time: ";
	DrawString(time.append(std::to_string((clock() - start_time) / CLOCKS_PER_SEC)).c_str(), &position, &colour);

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

void Source::DrawString(const char* text, Vector3* position, Color* color)
{
	glPushMatrix();
	bool lights = glIsEnabled(GL_LIGHTING);
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glLoadIdentity();
	gluOrtho2D(0, windowWidth, 0, windowHeight);
	//glColor4f(color->r, color->g, color->b, 0.0f);
	glRasterPos2i(position->x, position->y);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	if (lights)
		glEnable(GL_LIGHTING);
	glPopMatrix();

	// vvvvvvvvvv Tutorial Code vvvvvvvvvv

	/*glPushMatrix();

	glTranslatef(position->x, position->y, position->z);
	glRasterPos2f(0.0f, 0.0f);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);

	glPopMatrix();*/
}

void Source::Keyboard(unsigned char key, int x, int y, bool keyUp)
{
	if (key == 'q')
		_player_rotateLeft = !keyUp;
	else if (key == 'e')
		_player_rotateRight = !keyUp;
	/*if (key == 'r')
		camera->lookingAtPos.x += 2.0f;
	else if (key == 't')
		camera->lookingAtPos.x -= 2.0f;*/
	if (key == 'c' && !keyUp)
		std::cout << _player->GetPosition() << std::endl;

	if (key == 'w')
	{
		_player_forwards = !keyUp;
	}
	if (key == 's')
	{
		_player_backwards = !keyUp;
	}
	if (key == 'a')
	{
		_player_left = !keyUp;
	}
	if (key == 'd')
	{
		_player_right = !keyUp;
	}
	if (key == ' ')
	{
		_player_up = !keyUp;
	}
	if (key == 'x')
	{
		_player_down = !keyUp;
	}
	//std::cout << key << std::endl;

}

bool Source::InRange(float comparison, float bound1, float bound2)
{
	if (bound1 < bound2)
	{
		return bound1 <= comparison && comparison <= bound2;
	}
	else if (bound2 < bound1) {
		return bound2 <= comparison && comparison <= bound1;
	}
	else
		return false;
}
