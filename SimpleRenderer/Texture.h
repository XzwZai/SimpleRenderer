#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include "VMath.h"
class Texture
{
public:
	float* data;
	int rows, cols;
	Texture() {}
	Texture(string path)
	{
		cv::Mat m = cv::imread(path);
		data = (float*)calloc(m.rows*m.cols * 3, sizeof(float));
		rows = m.rows; cols = m.cols;
		int i = 0;
		for (int r = 0; r < rows; r++) {
			uchar *p = m.ptr(r);
			for (int c = 0; c < cols; c++) {
				int base = (r * cols + c) * 3;
				data[base] = p[c * 3 + 2] / 255.0f;
				data[base + 1] = p[c * 3 + 1] / 255.0f;
				data[base + 2] = p[c * 3] / 255.0f;				
			}
		}		
		
	}

	Color getColor(Vec2 t_pos)
	{
		Vec2 pos = Vec2(round(t_pos.x * (cols - 1)),round(t_pos.y * (rows - 1)));
		int base = (pos.y * cols + pos.x) * 3;
		return Color(data[base], data[base + 1], data[base + 2]);
	}
};
