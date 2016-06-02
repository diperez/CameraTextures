#include <vector>
#include "Camera2.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct point
{
	float x;
	float y;
	float z;
};
struct face
{
	vector<int> VV;
	vector<int> VT;
	vector<int> VN;
};
struct boundingbox
{
	point max;
	point min;
	point centro;
};
class OBJmodel3D
{
	public:
	boundingbox bb;
	vector <face> Faces;
	vector <point> Points;
	vector <point> Texture;
	vector <point> Normal;
	OBJmodel3D();
	void MakeModel(char * name);
	void MakeModel2(char *name);
	void DrawModel();
	void MakeBB(point P);
	void Normalize();
	float Abs(float A);
	float Max(float A, float B);
};