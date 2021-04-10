#include "MeshLoader.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

namespace MeshLoader
{
	void LoadVertices(ifstream& inFile, Mesh& mesh);
	void LoadNormals(ifstream& inFile, Mesh& mesh);
	void LoadTexCoords(ifstream& inFile, Mesh& mesh);
	void LoadIndices(ifstream& inFile, Mesh& mesh);

	void LoadVertices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.VertexCount;

		if (mesh.VertexCount > 0)
		{
			mesh.Vertices = new Vertex[mesh.VertexCount];

			for (int i = 0; i < mesh.VertexCount; i++)
			{
				inFile >> mesh.Vertices[i].x;
				inFile >> mesh.Vertices[i].y;
				inFile >> mesh.Vertices[i].z;
			}
		}
	}

	void LoadNormals(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.NormalCount;

		if (mesh.NormalCount > 0)
		{
			mesh.Normals = new Vector3[mesh.NormalCount];

			for (int i = 0; i < mesh.NormalCount; i++)
			{
				inFile >> mesh.Normals[i].x;
				inFile >> mesh.Normals[i].y;
				inFile >> mesh.Normals[i].z;
			}
		}
	}

	void LoadTexCoords(ifstream& inFile, Mesh& mesh)
	{

		inFile >> mesh.TexCoordCount;

		if (mesh.TexCoordCount > 0)
		{
			mesh.TexCoords = new TexCoord[mesh.TexCoordCount];

			for (int i = 0; i < mesh.TexCoordCount; i += 1)
			{
				inFile >> mesh.TexCoords[i].u;
				inFile >> mesh.TexCoords[i].v;
			}
		}
	}

	void LoadIndices(ifstream& inFile, Mesh& mesh)
	{

		inFile >> mesh.IndexCount;

		if (mesh.IndexCount > 0)
		{
			mesh.Indices = new GLushort[mesh.IndexCount];

			for (int i = 0; i < mesh.IndexCount; i += 1)
			{
				inFile >> mesh.Indices[i];
			}
		}
	}

	Mesh* MeshLoader::Load(char* path, char* texPath, int width, int height)
	{
		Mesh* mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())
		{
			cerr << "Can't open Mesh file " << path << endl;
			return nullptr;
		}


		LoadVertices(inFile, *mesh);
		LoadTexCoords(inFile, *mesh);
		LoadNormals(inFile, *mesh);
		LoadIndices(inFile, *mesh);


		mesh->_texture = new Texture2D();
		mesh->_texture->Load(texPath, width, height);
		//texmesh->_texture->LoadBitMap((char*)"test.bmp");

		return mesh;
	}

	Mesh* MeshLoader::LoadObj(char* path, char* texPath)
	{
		Mesh* mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())
		{
			cerr << "Can't open Obj file " << path << endl;
			return nullptr;
		}

		string read;
		vector<Vertex> vertices;
		vector<TexCoord> textureCoords;
		vector<TexCoord> textureBuffer;
		vector<Vector3> normals;
		vector<Vector3> normalBuffer;
		vector<GLushort> indecies;
		while (true)
		{
			inFile >> read;
			if (inFile.eof())
				break;
			if (read == "v") // Vertex
			{
				Vertex v;
				inFile >> v.x;
				inFile >> v.y;
				inFile >> v.z;
				vertices.push_back(v);
				//cout << "v " << v.x << " " << v.y << " " << v.z << endl;
			}
			else if (read == "vt") // UV Mapping
			{
				TexCoord tc;
				inFile >> tc.u;
				inFile >> tc.v;
				textureCoords.push_back(tc);
				//cout << "vt " << tc.u << " " << tc.v << endl;
			}
			else if (read == "vn") // Normal Mapping
			{
				Vector3 v3;
				inFile >> v3.x;
				inFile >> v3.y;
				inFile >> v3.z;
				normals.push_back(v3);
				//cout << "vn " << v3.x << " " << v3.y << " " << v3.z << endl;
			}
			else if (read == "f")
			{
				string data;
				GLushort s;
				string index;
				double d;

				// f <vertex>/<texture coord>/<normal> (2 more triplets in this order)

				inFile >> data;
				index = data.substr(0, data.find("/"));
				d = ::atof(index.c_str());
				s = d - 1;
				indecies.push_back(s);

				index = data.substr(data.find("/") + 1, data.length());
				d = ::atof(index.c_str());
				s = d - 1;
				textureBuffer.push_back(textureCoords.at(s));

				index = index.substr(index.find("/") + 1, index.length());
				d = ::atof(index.c_str());
				s = d - 1;
				normalBuffer.push_back(normals.at(s));

				//cout << "face " << s;

				inFile >> data;
				index = data.substr(0, data.find("/"));
				d = ::atof(index.c_str());
				s = d - 1;
				indecies.push_back(s);

				index = data.substr(data.find("/") + 1, data.length());
				d = ::atof(index.c_str());
				s = d - 1;
				textureBuffer.push_back(textureCoords.at(s));

				index = index.substr(index.find("/") + 1, index.length());
				d = ::atof(index.c_str());
				s = d - 1;
				normalBuffer.push_back(normals.at(s));

				//cout << s;

				inFile >> data;
				index = data.substr(0, data.find("/"));
				d = ::atof(index.c_str());
				s = d - 1;
				indecies.push_back(s);

				index = data.substr(data.find("/") + 1, data.length());
				d = ::atof(index.c_str());
				s = d - 1;
				textureBuffer.push_back(textureCoords.at(s));

				index = index.substr(index.find("/") + 1, index.length());
				d = ::atof(index.c_str());
				s = d - 1;
				normalBuffer.push_back(normals.at(s));

				//cout << s << endl;
			}
		}

		mesh->IndexCount = indecies.size();

		mesh->Indices = new GLushort[indecies.size()];
		for (int i = 0; i < indecies.size(); i++)
			mesh->Indices[i] = indecies[i];

		mesh->TexCoords = new TexCoord[textureBuffer.size()];
		for (int i = 0; i < textureBuffer.size(); i++)
			mesh->TexCoords[i] = textureBuffer[i];
		//cout << textureBuffer[i].u << " " << textureBuffer[i].v << endl;

		mesh->Normals = new Vector3[normalBuffer.size()];
		for (int i = 0; i < normalBuffer.size(); i++)
			mesh->Normals[i] = normalBuffer[i];

		mesh->Vertices = new Vertex[vertices.size()];
		for (int i = 0; i < vertices.size(); i++)
			mesh->Vertices[i] = vertices[i];

		mesh->_texture = new Texture2D();
		//mesh->_texture->Load(texPath, width, height);
		mesh->_texture->LoadBitMap(texPath);

		return mesh;
	}
}
