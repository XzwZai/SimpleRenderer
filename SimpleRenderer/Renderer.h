#pragma once
#include "Camera.h"
#include "Window.h"
#include <opencv2/opencv.hpp>

class Renderer
{
public:
	Camera camera;	
	Window window;
	Renderer(Camera _camera,Window _window)
	{
		camera = _camera;
		window = _window;
	}

	void render(VAO vao,Mat4 model,int flag = DRAW_TRIANGLES)
	{
		vector<Vertex>& vec = vao.vertexs;		
		for (vector<Vertex>::iterator it = vec.begin(); it != vec.end(); it++) {
			Vec4 v1 = camera.LookAt * model * Vec4((*it).world_pos, 1.0f);
			Vec4 v = camera.projection * v1;
			(*it).clip_pos = Vec3(v.x / v.w, v.y / v.w, v.z / v.w);
		}
		window.drawVAO(vao, flag);
	}

};