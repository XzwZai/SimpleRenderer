#include <iostream>
#include "VAO.h"
#include "Window.h"
#include <opencv2/opencv.hpp>
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

	int width = 100, height = 100;
	Window window(width, height);
	/*window.drawLine(50, 50, 110, 90, RED, WHITE);
	window.drawLine(50, 100, 110, 60, RED, WHITE);*/
	/*window.drawLine(0, 0, 60, 1000, RED, WHITE);
	window.drawLine(0, 0, 60, 60, RED, WHITE);*/
	
	Vertex v0; v0.clip_pos = Pos(0, 0, 0); v0.color = Color(1, 0, 0);
	Vertex v1; v1.clip_pos = Pos(1, 1, 0); v1.color = Color(0, 1, 0);
	Vertex v2; v2.clip_pos = Pos(1, 0, 0); v2.color = Color(0, 0, 1);
	//window.AntiClockTriangle(v0, v1, v2);
	window.drawTriangle(v0, v1, v2);
	int *frame = window.frameBuffer;
	cv::Mat M(height, width, CV_8UC3);
	for (int r = 0; r < height; r++) {
		uchar *p = M.ptr(r);
		for (int c = 0; c < width; c++) {
			if (frame[(r*width + c) * 3] != 0) {
				c = c;
			}
			p[c * 3] = frame[(r*width + c) * 3 + 2];
			p[c * 3 + 1] = frame[(r*width + c) * 3 + 1];
			p[c * 3 + 2] = frame[(r*width + c) * 3];
		}
	}

	

	imshow("1", M);
	cv::waitKey(0);
}