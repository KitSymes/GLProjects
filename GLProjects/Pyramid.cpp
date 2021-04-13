#include "Pyramid.h"

Pyramid::Pyramid(Mesh* mesh, GLfloat x, GLfloat y, GLfloat z) : SceneObject(mesh)
{
	_x = x;
	_y = y;
	_z = z;
}

Pyramid::~Pyramid()
{
}

void Pyramid::SetRotation(GLfloat rotationX, GLfloat rotationY, GLfloat rotationZ)
{
	_rotationX = rotationX;
	_rotationY = rotationY;
	_rotationZ = rotationZ;
}

void Pyramid::Draw()
{
	if (_mesh != nullptr) {
		glBindTexture(GL_TEXTURE_2D, _mesh->_texture->GetID());
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);
		glNormalPointer(GL_FLOAT, 0, _mesh->Normals);

		glPushMatrix();
		glRotatef(_rotationX, 1.0f, 0.0f, 0.0f);
		glRotatef(_rotationY, 0.0f, 1.0f, 0.0f);
		glRotatef(_rotationZ, 0.0f, 0.0f, 1.0f);
		glTranslatef(_x, _y, _z);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, _mesh->Indices);
		glPopMatrix();

		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

void Pyramid::Update()
{
	_rotationX += 1;
	_rotationY += 1;
	_rotationZ += 1;
}
