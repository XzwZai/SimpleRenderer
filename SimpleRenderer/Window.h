#pragma once
#include "VAO.h"
#include "Color.h"
class Window
{
public:
	int width, height, channel;
	int* frameBuffer;
	Window(int _width, int _height,int _channel = 3) {
		width = _width;
		height = _height;
		channel = _channel;
		frameBuffer = (int*)calloc(width * height * channel, sizeof(int));
	}

	void drawPoint(int x,int y,Color c) 
	{		
		frameBuffer[(y * width + x) * 3] = c.R; frameBuffer[(y * width + x) * 3] = c.G; frameBuffer[(y * width + x) * 3] = c.B;				
	}

	void drawLine(int x1, int y1, int x2, int y2)
	{

	}

};

