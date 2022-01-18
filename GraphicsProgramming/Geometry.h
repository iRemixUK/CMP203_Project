#pragma once
#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
// Further includes should go here:
#include "SOIL.h"
#include <vector>
class Geometry
{
public:
	void render_stand();
	void render_sphere();
	void render_disc(GLuint texture);
	void solarSystem();
	void spheres();
};

