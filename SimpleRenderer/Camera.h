#pragma once
#include "VMath.h"
#include <math.h>
class Camera
{
public:
	Vec3 pos, target;
	Vec3 direction, up, right;
	float fov, near, far, wlRatio;
	Mat4 LookAt,projection;
	Camera() {}
	Camera(Vec3 _pos, Vec3 _target, Vec3 _up,float _wlRatio, float _fov = 90.0f, float _near = 0.1f, float _far = 1000.0f) {
		pos = _pos;
		target = _target;
		up = _up;
		fov = _fov;
		near = _near;
		far = _far;
		wlRatio = _wlRatio;
		direction = (target - pos).norm();
		right = direction.cross(up);
		LookAt = Mat4(right, up, direction);
		LookAt.mat[12] = -pos.x;
		LookAt.mat[13] = -pos.y;
		LookAt.mat[14] = -pos.z;
		projection.mat[0] = 1.0 / (wlRatio * tan(fov*PI/360));
		projection.mat[5] = 1.0 / (tan(fov*PI / 360));
		projection.mat[10] = far / (far - near);
		projection.mat[11] = 1;
		projection.mat[14] = -far * near / (far - near);
	}
};