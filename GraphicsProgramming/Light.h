// Class to handle lights 
// Include GLUT, openGL, input.
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
// Further includes should go here:
#include "SOIL.h"
#include <vector>
class Light
{
public:
	void spotlight();
	void spotlight2();
	void spotlight3();
	void sunlight();
	void rotating(float angle);
	void shadow();
	void colours(int keystate);

private:
	float r = 1;
	float g = 1;
	float b = 1;
};

