#include "Player.h"

Player::Player(GLfloat x, GLfloat y, GLfloat z) : SceneObject()
{
	_mesh = MeshLoader::LoadObj((char*)"Resources/Models/fighter.obj", (char*)"Resources/Textures/Player.bmp");

	_x = x;
	_y = y;
	_z = z;

	_material = new Material();
	_material->Shininess = 100.0f;

	_material->Ambient.x = 0.8;
	_material->Ambient.y = 0.05;
	_material->Ambient.z = 0.05;
	_material->Ambient.w = 1.0;

	_material->Diffuse.x = 0.8;
	_material->Diffuse.y = 0.05;
	_material->Diffuse.z = 0.05;
	_material->Diffuse.w = 1.0;

	_material->Specular.x = 1.0;
	_material->Specular.y = 1.0;
	_material->Specular.z = 1.0;
	_material->Specular.w = 1.0;
}

Player::~Player()
{
	delete _material;
}

void Player::Draw()
{
	if (_mesh != nullptr) {
		glBindTexture(GL_TEXTURE_2D, _mesh->_texture->GetID());
		/*glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);
		glNormalPointer(GL_FLOAT, 0, _mesh->Normals);*/
		glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
		glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->Diffuse.x));
		glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->Specular.x));
		glMaterialfv(GL_FRONT, GL_SHININESS, &(_material->Shininess));

		glPushMatrix();
		glRotatef(_rotationX, 1.0f, 0.0f, 0.0f);
		glRotatef(_rotationY, 0.0f, 1.0f, 0.0f);
		glRotatef(_rotationZ, 0.0f, 0.0f, 1.0f);
		glTranslatef(_x, _y, _z);
		glBegin(GL_TRIANGLES);
		for (int i = 0; i < _mesh->IndexCount; i++)
		{
			TexCoord tc = _mesh->TexCoords[i];
			glTexCoord2f(tc.u, tc.v);
			Vector3 n = _mesh->Normals[i];
			glNormal3f(n.x, n.y, n.z);
			Vertex v = _mesh->Vertices[_mesh->Indices[i]];
			glVertex3f(v.x, v.y, v.z);
		}
		glEnd();
		glPopMatrix();

		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

void Player::Update()
{
	/*_rotationX += 1;
	_rotationY += 1;
	_rotationZ += 1;*/
}