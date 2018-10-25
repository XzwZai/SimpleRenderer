#include <iostream>
#include "VAO.h"
using namespace std;

int main()
{
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	VAO vao;
	Vertex v;
	vao.BindBuffer(vertices, sizeof(vertices) / sizeof(float), 0);
	if (vao.GenVertexs())
	{
		vector<Vertex> vs = vao.getvertexs();
		for (vector<Vertex>::iterator it = vs.begin(); it != vs.end(); it++) {
			cout << (*it).tostring() << endl;
		}
	}
}