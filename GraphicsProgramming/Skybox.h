#pragma once
// Include GLUT, openGL, input.
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
// Further includes should go here:
#include "SOIL.h"
#include <vector>
class Skybox
{
public:
	Skybox();
	~Skybox();
	void drawSkybox();
	void render();

private:
	GLuint skybox;
};
