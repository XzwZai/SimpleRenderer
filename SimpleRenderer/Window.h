#pragma once
#include "VAO.h"
#include "VMath.h"
class Window
{
public:
	int width, height, channel;
	Color bgColor;	
	int* frameBuffer;
	Window(int _width, int _height,int _channel = 3,Color _bgColor = Color()) {
		width = _width;
		height = _height;
		channel = _channel;
		frameBuffer = (int*)calloc(width * height * channel, sizeof(int));
		for (int i = 0; i < width * height; i++) {
			frameBuffer[i * 3]     = bgColor.x;
			frameBuffer[i * 3 + 1] = bgColor.y;
			frameBuffer[i * 3 + 2] = bgColor.z;
		}
	}

	Color interpColor(int s,int t,int m,Color c0,Color c1) {
		float k = (float)(m - s) / (t - s);
		Color c = c0 * (1 - k) + c1 * k;
		return c;
	}

	int cvtColor(float c)
	{
		int t = round(c * 255);
		return t;
	}

	void drawPoint(int x,int y,Color c) 
	{		
		frameBuffer[(y * width + x) * 3] = cvtColor(c.x); frameBuffer[(y * width + x) * 3 + 1] = cvtColor(c.y); frameBuffer[(y * width + x) * 3 + 2] = cvtColor(c.z);
	}

	void drawLine(int x0,int y0,int x1,int y1,Color c0,Color c1) {
		x0 = x0 < 0 ? 0 : x0;
		y0 = y0 < 0 ? 0 : y0 >= height ? height - 1 : y0;
		x1 = x1 < 0 ? 0 : x1 >= width ? width - 1 : x1;
		y1 = y1 < 0 ? 0 : y1 >= height ? height - 1 : y1;
		if (x0 == x1) {
			for (int y = y0; y <= y1; y++) {
				drawPoint(x0, y, interpColor(y0, y1, y, c0, c1));
			}
			return;
		}
		if (y0 == y1) {
			for (int x = x0; x <= x1; x++) {
				drawPoint(x, y0, interpColor(x0, x1, x, c0, c1));
			}
			return;
		}
		if (y1 - y0 < x0 - x1) {

		}
		else if (y1 - y0 < 0 && y1 - y0 > x0 - x1) {
			int y = y0;
			int d = 2 * (y0 - y1)*(x0 + 1) + (x1 - x0)*(2 * y0 + 1) + 2 * x0*y1 - 2 * x1*y0;
			for (int x = x0; x <= x1; x++) {
				drawPoint(x, y, interpColor(x0, x1, x, c0, c1));
				if (d > 0) {
					y--;
					d += -2 * (x1 - x0) + 2 * (y0 - y1);
				}
				else {
					d += 2 * (y0 - y1);
				}
			}
		}
		else if (y1 - y0 > 0 && y1 - y0 < x1 - x0) {
			int y = y0;
			int d = 2 * (y0 - y1)*(x0 + 1) + (x1 - x0)*(2 * y0 + 1) + 2 * x0*y1 - 2 * x1*y0;
			for (int x = x0; x <= x1; x++) {
				drawPoint(x, y, interpColor(x0, x1, x, c0, c1));
				if (d < 0) {
					y++;
					d += 2 * (x1 - x0) + 2 * (y0 - y1);
				}
				else {
					d += 2 * (y0 - y1);
				}
			}
		}
		else {

		}	
	}

	void drawLine(Vertex v0, Vertex v1)
	{
		int x0, y0, x1, y1;
		Color c0, c1;
		if (v0.u < v1.u || (v0.u == v1.u && v0.v < v1.v)) {
			x0 = round(v0.u);
			y0 = round(v0.v);
			c0 = Color(v0.r, v0.g, v0.b);
			x1 = round(v1.u);
			y1 = round(v1.v);
			c1 = Color(v1.r, v1.g, v1.b);
		}
		else {
			x0 = round(v1.u);
			y0 = round(v1.v);
			c0 = Color(v1.r, v1.g, v1.b);
			x1 = round(v0.u);
			y1 = round(v0.v);
			c1 = Color(v0.r, v0.g, v0.b);
		}
		x0 = x0 < 0 ? 0 : x0;
		y0 = y0 < 0 ? 0 : y0 >= height ? height - 1 : y0;
		x1 = x1 < 0 ? 0 : x1 >= width ? width - 1 : x1;
		y1 = y1 < 0 ? 0 : y1 >= height ? height - 1 : y1;
		drawLine(x0, y0, x1, y1, c0, c1);

	}
};

