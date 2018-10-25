#pragma once
#include <vector>
#include <string>
#define V_COLOR		1 << 2
#define V_NORMAL	1 << 1
#define V_TEX		1 << 0
using namespace std;
struct Vertex
{
	float x, y, z;
	float r, g, b;
	float nx, ny, nz;
	float tx, ty;
	string tostring()
	{
		return "(" + to_string(x) + " ," + to_string(y) + " ," + to_string(z) + " )";
	}
};

class VAO
{
public:
	float* VBuffer;
	int size;
	vector<Vertex> vertexs;
	//void BindBuffer(float* buffer, unsigned int _size, unsigned int flag) {};
	void BindBuffer(float* buffer, unsigned int _size, unsigned int flag)
	{
		VBuffer = buffer;
		size = _size;
		color = flag & V_COLOR;
		normal = flag & V_NORMAL;
		texture = flag & V_TEX;
	}

	bool GenVertexs()
	{
		int step = (color + normal) * 3 + texture * 2 + 3;
		if (size % step != 0) {
			return false;
		}
		int count = size / step;
		int index = 0;
		for (int i = 0; i < count; i++) {
			Vertex v;
			v.x = VBuffer[index++];
			v.y = VBuffer[index++];
			v.z = VBuffer[index++];
			v.r = !color ? 0 : VBuffer[index++];
			v.g = !color ? 0 : VBuffer[index++];
			v.b = !color ? 0 : VBuffer[index++];
			v.nx = !normal ? 0 : VBuffer[index++];
			v.ny = !normal ? 0 : VBuffer[index++];
			v.nz = !normal ? 0 : VBuffer[index++];
			v.tx = !texture ? 0 : VBuffer[index++];
			v.ty = !texture ? 0 : VBuffer[index++];
			vertexs.push_back(v);
		}
	}

	vector<Vertex> getvertexs() { return vertexs; }
private:
	int color;
	int normal;
	int texture;
};





