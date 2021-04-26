#include "GenericObject.h"

GenericObject::GenericObject(Mesh* mesh, GLfloat x, GLfloat y, GLfloat z) : SceneObject(mesh)
{
	_x = x;
	_y = y;
	_z = z;

	_material = new Material();
	_material->Shininess = 0.0f;

	_material->Ambient.x = 0.05 * 10;
	_material->Ambient.y = 0.05 * 10;
	_material->Ambient.z = 0.05 * 10;
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

GenericObject::~GenericObject()
{
	delete _material;
}

void GenericObject::Draw()
{
	if (_mesh != nullptr) {
		glBindTexture(GL_TEXTURE_2D, _mesh->_texture->GetID());
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

	if (sibling != nullptr)
		sibling->Draw();
	if (child != nullptr)
		child->Draw();
}

void GenericObject::Update()
{

}