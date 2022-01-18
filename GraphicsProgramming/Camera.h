#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
#include <math.h>
#include "Vector3.h"
class Camera
{
public:
	Camera();
	~Camera();
	void handleInput(float dt);
	void update(float dt);
	void setInput(Input* in) { input = in; };
	void cams(int keystate);
	void SetPosition();
	Vector3 Position();
	Vector3 LookAt();
	Vector3 Up();

private:
	float Yaw;
	float Pitch;
	float Roll;
	float mouseX;
	float mouseY;
	float width;
	float height;
	float elapsedTime;
	Vector3 position, forward, up, right, Lookat;
	Input* input;
};