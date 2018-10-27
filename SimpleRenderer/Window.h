#pragma once
#include "VAO.h"
#include "VMath.h"
#define u2x(u) round((u + 1) * width / 2)
#define v2y(v) round((1 - v) * height / 2)
class Window
{
public:
	int width, height, channel;
	Color bgColor;	
	int* frameBuffer;
	Window() {}
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

	bool isInWindow(int x, int y)
	{
		return x < width && x >= 0 && y < height && y >= 0;
	}

	int cvtColor(float c)
	{
		int t = round(c * 255);
		return t;
	}	

	void drawPoint(int x,int y,Color c) 
	{		
		if (isInWindow(x,y)) {
			frameBuffer[(y * width + x) * 3] = cvtColor(c.x); frameBuffer[(y * width + x) * 3 + 1] = cvtColor(c.y); frameBuffer[(y * width + x) * 3 + 2] = cvtColor(c.z);
		}
	}

	void drawLine(int x0,int y0,int x1,int y1,Color c0,Color c1) {
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
		if (y1 - y0 <= x0 - x1) {
			int x = x1;
			int d = (y0 - y1) * (2 * x0 + 1) + 2 * (x1 - x0)*(y0 + 1) + 2 * x0*y1 - 2 * x1*y0;
			for (int y = y1; y <= y0; y++) {
				drawPoint(x, y, interpColor(y0, y1, y, c0, c1));
				if (d > 0) {
					x--;
					d += 2 * (x1 - x0) - 2 * (y0 - y1);
				}
				else {
					d += 2 * (x1 - x0);
				}
			}
		}
		else if (y1 - y0 <= 0 && y1 - y0 > x0 - x1) {
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
		else if (y1 - y0 > 0 && y1 - y0 <= x1 - x0) {
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
			int x = x0;
			int d = (y0 - y1) * (2 * x0 + 1) + 2 * (x1 - x0)*(y0 + 1) + 2 * x0*y1 - 2 * x1*y0;
			for (int y = y0; y <= y1; y++) {
				drawPoint(x, y, interpColor(y0, y1, y, c0, c1));
				if (d > 0) {
					x++;
					d += 2 * (x1 - x0) + 2 * (y0 - y1);
				}
				else {
					d += 2 * (x1 - x0);
				}
			}
		}	
	}

	void drawLine(Vertex v0, Vertex v1)
	{
		int x0, y0, x1, y1;
		Color color0, color1;
		if (v0.clip_pos.x < v1.clip_pos.x || (v0.clip_pos.x == v1.clip_pos.x && v0.clip_pos.y < v1.clip_pos.y)) {
			x0 = u2x(v0.clip_pos.x);
			y0 = v2y(v0.clip_pos.y);
			color0 = v0.color;
			x1 = u2x(v1.clip_pos.x);
			y1 = v2y(v1.clip_pos.y);
			color1 = v1.color;
		}
		else {
			x1 = u2x(v0.clip_pos.x);
			y1 = v2y(v0.clip_pos.y);
			color1 = v0.color;
			x0 = u2x(v1.clip_pos.x);
			y0 = v2y(v1.clip_pos.y);
			color0 = v1.color;			
		}				
		drawLine(x0, y0, x1, y1, color0, color1);

	}

	float edgeFunction(int x0, int y0, int x1, int y1, int x, int y)
	{
		if (x1 == x0) {
			return -(y1 - y0) * (x - x0);
		}
		else {
			return (x1 - x0) * y - (y1 - y0) * x - x1 * y0 + y1 * x0;
		}
	}

	void AntiClockTriangle(Vertex &v0, Vertex &v1, Vertex &v2) 
	{
		if (edgeFunction(u2x(v0.clip_pos.x), v2y(v0.clip_pos.y), u2x(v1.clip_pos.x), v2y(v1.clip_pos.y), u2x(v2.clip_pos.x), v2y(v2.clip_pos.y)) < 0) {
			Vertex t = v1;
			v1 = v0;
			v0 = t;
		}
	}

	void drawTriangle(Vertex v0, Vertex v1, Vertex v2) 
	{
		AntiClockTriangle(v0, v1, v2);
		int x0 = u2x(v0.clip_pos.x), y0 = v2y(v0.clip_pos.y), x1 = u2x(v1.clip_pos.x), y1 = v2y(v1.clip_pos.y), x2 = u2x(v2.clip_pos.x), y2 = v2y(v2.clip_pos.y);
		Color color0 = v0.color, color1 = v1.color, color2 = v2.color;
		int maxX = max(x0, x1, x2), maxY = max(y0, y1, y2), minX = min(x0, x1, x2), minY = min(y0, y1, y2);
		for (int y = minY; y <= maxY; y++) {
			for (int x = minX; x <= maxX; x++) {
				float sigma0 = (float)((y1 - y2)*(x - x2) + (x2 - x1)*(y - y2)) / ((y1 - y2)*(x0 - x2) + (x2 - x1)*(y0 - y2));
				float sigma1 = (float)((y2 - y0)*(x - x2) + (x0 - x2)*(y - y2)) / ((y1 - y2)*(x0 - x2) + (x2 - x1)*(y0 - y2));
				float sigma2 = 1 - sigma0 - sigma1;
				if (sigma0 >= 0 && sigma0 <= 1 && sigma1 >= 0 && sigma1 <= 1 && sigma2 >= 0 && sigma2 <= 1) {
					drawPoint(x, y, color0 * sigma0 + color1 * sigma1 + color2 * sigma2);
				}
			}
		}
	}

	void drawVAO(VAO vao,int flag)
	{
		if (vao.vertexs.size % 3 != 0) {
			return;
		}
		for (vector<Vertex>::iterator it = vao.vertexs.begin(); it != vao.vertexs.end(); it++) {
			Vertex v0 = *it; it++;
			Vertex v1 = *it; it++;
			Vertex v2 = *it; 
			drawTriangle(v0, v1, v2);
		}
	}

};

