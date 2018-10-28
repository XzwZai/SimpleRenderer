#pragma once
#include <vector>
#include <string>
#include "VMath.h"
#define V_COLOR		1 << 2
#define V_NORMAL	1 << 1
#define V_TEX		1 << 0
using namespace std;
struct Vertex
{
	Pos world_pos;
	Color color;
	Normal normal;
	Pos clip_pos;
	float tx, ty;
	string tostring()
	{
		return "worldPos : " + world_pos.toString() + " color : " + color.toString();
	}
};

class VAO
{
public:
	float* vBuffer;
	int size;
	vector<Vertex> vertexs;
	//void BindBuffer(float* buffer, unsigned int _size, unsigned int flag) {};
	void BindBuffer(float* buffer, unsigned int _size, unsigned int flag)
	{
		vBuffer = buffer;
		size = _size;
		color = (flag & V_COLOR) == 0 ? 0 : 1;
		normal = (flag & V_NORMAL) == 0 ? 0 : 1;
		texture = (flag & V_TEX) == 0 ? 0 : 1;
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
			v.world_pos = Pos(vBuffer[index], vBuffer[index + 1], vBuffer[index + 2]); index += 3;
			v.color = Color(!color ? 0 : vBuffer[index], !color ? 0 : vBuffer[index + 1], !color ? 0 : vBuffer[index + 2]); index += color ? 0 : 3;
			v.normal = Normal(!normal ? 0 : vBuffer[index], !normal ? 0 : vBuffer[index + 1], !normal ? 0 : vBuffer[index + 2]); index += normal ? 0 : 3;
			v.tx = !texture ? 0 : vBuffer[index++];
			v.ty = !texture ? 0 : vBuffer[index++];
			v.clip_pos = Pos();
			vertexs.push_back(v);
		}
		return true;
	}

	vector<Vertex> getvertexs() { return vertexs; }
private:
	int color;
	int normal;
	int texture;
};





