#include <iostream>
#include "VAO.h"
#include "Window.h"
#include "Camera.h"
#include "Renderer.h"
#include <opencv2/opencv.hpp>
using namespace std;
int main()
{
	int width = 800, height = 600;
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
		-0.5f, -0.5f, -0.5f,1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f,1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f,  0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f,  1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,   1.0f, 0.0f, 0.0f,

		0.5f, 0.5f, 0.5f,  1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f,   1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,

		-0.5f, 0.5f, -0.5f,1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f

	};

	/*float vertices[] = {
		0,0,0,0,1,0,
		0,0,-1,0,0,1
	};*/

	VAO vao;
	Vertex v;
	vao.BindBuffer(vertices, sizeof(vertices) / sizeof(float), V_COLOR);
	vao.GenVertexs();
	for (vector<Vertex>::iterator it = vao.vertexs.begin(); it != vao.vertexs.end(); it++)
	{
		cout << (*it).tostring() << endl;
	}
	Window window(width, height);
	Camera camera(Vec3(0, 0, 3), Vec3(0, 0, 0), Vec3(0, 1, 0), (float)width / height);
	Renderer renderer(camera,window);
	//renderer.render(vao, Mat4(), DRAW_POINTS);
	for (int i = 0; i < 10; i++) {
		renderer.render(vao, translationMat(cubePositions[i]));
	}
	//renderer.render(vao, Mat4());

	//window.AntiClockTriangle(v0, v1, v2);
	float *frame = renderer.window.frameBuffer;
	cv::Mat M(height, width, CV_8UC3);
	for (int r = 0; r < height; r++) {
		uchar *p = M.ptr(r);
		for (int c = 0; c < width; c++) {
			p[c * 3] = frame[(r*width + c) * 4 + 2];
			p[c * 3 + 1] = frame[(r*width + c) * 4 + 1];
			p[c * 3 + 2] = frame[(r*width + c) * 4];
		}
	}

	

	imshow("1", M);
	cv::waitKey(0);
}