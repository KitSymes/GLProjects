#define _CRT_SECURE_NO_DEPRECATE
#include "Texture2D.h"
#include <iostream>
#include <fstream>
using namespace std;

Texture2D::Texture2D()
{

}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &_ID);
}

bool Texture2D::Load(char* path, int width, int height)
{
	char* tempTextureData;
	int fileSize;
	ifstream inFile;
	_width = width;
	_height = height;
	inFile.open(path, ios::binary);

	if (!inFile.good())
	{
		cerr << "Cannot open file " << path << endl;
		return false;
	}

	inFile.seekg(0, ios::end);
	fileSize = (int)inFile.tellg();
	tempTextureData = new char[fileSize];
	inFile.seekg(0, ios::beg);
	inFile.read(tempTextureData, fileSize);
	inFile.close();

	glGenTextures(1, &_ID);
	glBindTexture(GL_TEXTURE_2D, _ID);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);

	delete[] tempTextureData;
	return true;
}

void Texture2D::LoadBitMap(char* filename)
{
	int i;
	FILE* f = fopen(filename, "rb");
	unsigned char info[54];

	fread(info, sizeof(unsigned char), 54, f); // Read Header
	int width = *(int*)&info[18]; // Width is at byte 18
	int height = *(int*)&info[22]; // Height is at byte 22

	//cout << width << " " << height << endl;

	int size = 3 * width * height; // 3 bytes per pixel when saved in 24 bit depth
	unsigned char* image = new unsigned char[size];
	fread(image, sizeof(unsigned char), size, f);
	fclose(f);

	for (i = 0; i < size; i += 3) // Flip from BGR to RGB
	{
		unsigned char b = image[i];
		image[i] = image[i + 2]; // B = R
		image[i + 2] = b; // R = B
	}

	glGenTextures(1, &_ID);
	glBindTexture(GL_TEXTURE_2D, _ID);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, image);

	delete[] image; // Delete old data
}