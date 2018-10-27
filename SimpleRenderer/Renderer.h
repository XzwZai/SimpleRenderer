#pragma once
#include "VAO.h"
#include "Camera.h"
#include "Window.h"
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

	void render(VAO vao,Mat4 model)
	{
		vector<Vertex>& vec = vao.vertexs;		
		for (vector<Vertex>::iterator it = vec.begin(); it != vec.end(); it++) {
			Vec4 v = camera.projection * camera.LookAt * model * Vec4((*it).world_pos,1.0f);
			(*it).clip_pos = Vec3(v.x, v.y, v.z);
		}
		
	}

};