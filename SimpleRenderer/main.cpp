#include <iostream>
#include <time.h>
#include <Windows.h>
#include <opencv2/opencv.hpp>
#include "Renderer.h"

using namespace std;

int width = 800, height = 600;

int main()
{
	bool active = true;
	//int width = 100, height = 100;
	Vec3 cubePositions[] = {
	Vec3(0.0f,  0.0f,  0.0f),
	Vec3(2.0f,  5.0f, -15.0f),
	Vec3(-1.5f, -2.2f, -2.5f),
	Vec3(-3.8f, -2.0f, -12.3f),
	Vec3(2.4f, -0.4f, -3.5f),
	Vec3(-1.7f,  3.0f, -7.5f),
	Vec3(1.3f, -2.0f, -2.5f),
	Vec3(1.5f,  2.0f, -2.5f),
	Vec3(1.5f,  0.2f, -1.5f),
	Vec3(-1.3f,  1.0f, -1.5f)
	};
	/*float vertices[] = {
	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f
	};*/
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,1.0f, 1.0f,
		0.5f, 0.5f, -0.5f,   0.0f, 0.0f, 1.0f,1.0f, 0.0f,
		0.5f, 0.5f, -0.5f,   0.0f, 0.0f, 1.0f,1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,0.0f, 1.0f,

		-0.5f, -0.5f, 0.5f,1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f,  0.0f, 1.0f, 0.0f,1.0f, 1.0f,
		0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,1.0f, 0.0f,
		0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,0.0f, 1.0f,

		-0.5f, 0.5f, 0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,   1.0f, 0.0f, 0.0f,0.0f, 1.0f,

		0.5f, 0.5f, 0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,1.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f,   1.0f, 0.0f, 0.0f,0.0f, 1.0f,

		-0.5f, -0.5f, -0.5f,1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,1.0f, 1.0f,
		0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,1.0f, 0.0f,
		0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f,1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,1.0f, 1.0f,
		0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,1.0f, 0.0f,
		0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f

	};

	VAO vao;
	Vertex v;
	vao.BindBuffer(vertices, sizeof(vertices) / sizeof(float), V_COLOR | V_TEX);
	vao.GenVertexs();
	for (vector<Vertex>::iterator it = vao.vertexs.begin(); it != vao.vertexs.end(); it++)
	{
		cout << (*it).tostring() << endl;
	}
	Window window(width, height);
	Camera camera(Vec3(0, 0, 3), Vec3(0, 0, 0), Vec3(0, 1, 0), (float)width / height);
	Renderer renderer(camera,window);
	Texture texture("D://t2.png");
	//Texture texture("D://container.jpg");	
	DWORD t_start, t_end;
	t_start = GetTickCount();
	Vec3 ori(0.5, 0.0, 0.0);
	while (active) {
		DWORD t_end = GetTickCount();
		float t = (t_end - t_start) / 1000.0;
		std::cout << t << std::endl;
		renderer.clear();
		for (int i = 0; i < 10; i++) {
			renderer.render(vao, translationMat(cubePositions[i]) * translationMat(ori*t),2,&texture);
		}				
		renderer.window.display();		
	}
	
}