// Scene class. Configures a basic 3D scene.
// Interfaces with the Input class to handle user input
// Calculates and outputs Frames Per Second (FPS) rendered.
// Important functions are the constructor (initialising the scene), 
// update (for process user input and updating scene objects) and render (renders scene).
#ifndef _SCENE_H
#define _SCENE_H

// Include GLUT, openGL, input.
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
// Further includes should go here:
#include "SOIL.h"
#include <vector>
#include "Skybox.h"
#include "Camera.h"
#include "Geometry.h"
#include "Light.h"
#include "Model.h"
#include "Shadow.h"

class Scene
{

public:
	Scene(Input *in);
	// Main render function
	void render();
	// Handle input function that receives delta time from parent.
	void handleInput(float dt);
	// Update function receives delta time from parent (used for frame independent updating).
	void update(float dt);
	// Resizes the OpenGL output based on new window size.
	void resize(int w, int h);

protected:
	// configure opengl render pipeline
	void initialiseOpenGL();
	// Renders text (x, y positions, RGB colour of text, string of text to be rendered)
	void displayText(float x, float y, float r, float g, float b, char* string);
	// A function to collate all text output in a single location
	void renderTextOutput();
	void calculateFPS();

	// draw primitive functions
	Skybox skybox;
	Camera camera;
	Geometry geometry;
	Light light;
	Shadow shadow;

	Model lamp;
	Model jinx;
	Model leblanc;
	Model sniper;
	Model light2;
	Model teapot;
	Model yoda;

	void render_pillars();
	void reflected();
	void render_plane();
	void solarSystem();
	void disc();
	void Shadow();

	GLuint eyeball;
	float angle;
	float lightangle;
	float speed;
	int keystate;
	int camerastate;
	int posState;
	int camPos;
	bool rstate;

	// For access to user input.
	Input* input;
		
	// For Window and frustum calculation.
	int width, height;
	float fov, nearPlane, farPlane;

	// For FPS counter and mouse coordinate output.
	int frame = 0, time, timebase = 0;
	char fps[40];
	char mouseText[40];

	// For control text output
	char camMode[40];
	char modelSpeed[40];
	char wireframe[40];
	char spacebar[40];
	char staticCam[40];
};

#endif