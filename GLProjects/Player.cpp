#include "Player.h"

Player::Player(GLfloat x, GLfloat y, GLfloat z) : SceneObject()
{
	_mesh = MeshLoader::LoadObj((char*)"Resources/Models/fighter.obj");
	_mesh->_texture->LoadBitMap((char*)"Resources/Textures/Player.bmp");

	_x = x;
	_y = y;
	_z = z;

	_material = new Material();
	_material->Shininess = 255.0f;

	_material->Ambient.x = 0.05*5;
	_material->Ambient.y = 0.05*5;
	_material->Ambient.z = 0.05*5;
	_material->Ambient.w = 1.0;

	_material->Diffuse.x = 0.05 * 4;
	_material->Diffuse.y = 0.05 * 4;
	_material->Diffuse.z = 0.05 * 4;
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
		glTranslatef(_x, _y, _z);
		glRotatef(_rotationX, 1.0f, 0.0f, 0.0f);
		glRotatef(_rotationY, 0.0f, 1.0f, 0.0f);
		glRotatef(_rotationZ, 0.0f, 0.0f, 1.0f);
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
	float bound = 0.0002f;
	if (_velocity.x != 0)
	{
		_velocity.x += (_velocity.x > 0 ? -1 : 1) * (max(abs(_velocity.x) / 100, bound));
		if (-bound < _velocity.x && _velocity.x < bound)
			_velocity.x = 0;
	}
	if (_velocity.y != 0)
	{
		_velocity.y += (_velocity.y > 0 ? -1 : 1) * (max(abs(_velocity.y) / 100, bound));
		if (-bound < _velocity.y && _velocity.y < bound)
			_velocity.y = 0;
	}
	if (_velocity.z != 0)
	{
		_velocity.z += (_velocity.z > 0 ? -1 : 1) * (max(abs(_velocity.z) / 100, bound));
		if (-bound < _velocity.z && _velocity.z < bound)
			_velocity.z = 0;
	}

	Move(_velocity);
}