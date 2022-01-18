#include "Scene.h"

// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Scene::Scene(Input *in)
{
	// Store pointer for input class
	input = in;
	initialiseOpenGL();

	// Other OpenGL / render setting should be applied here.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//Loading in the models required
	lamp.load("models/2.obj", "gfx/wood2.jpg");
	jinx.load("models/jinx.obj", "gfx/jinx.png");
	leblanc.load("models/leblanc.obj", "gfx/leblanc.tga");
	sniper.load("models/AWP2.obj", "gfx/AWP.bmp");
	teapot.load("models/teapot.obj", "gfx/metal.jpg");
	yoda.load("models/Yoda.obj", "gfx/Yoda.png");

	// Loading in the eyeball texture for the disc
	eyeball = SOIL_load_OGL_texture(
		"gfx/eyeball.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	// Enabling everything needed
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	
	// Initialise scene variables
	camera.setInput(input); // passes input so it can be used to control the camera
	speed = 50.f;
	keystate = 0;
	camerastate = 0;
	camPos = 0;
	posState = 0;
	rstate = false;
}

void Scene::handleInput(float dt)
{
	// Handle user input
	if (input->isKeyDown(' ')) // This is to control the lighting on baby yoda
	{
		keystate = keystate + 1;
		if (keystate >= 4)
		{
			keystate = 0;
		}
		input->setKeyUp(' ');
	}

	if (input->isKeyDown('f') || input->isKeyDown('F')) // This is to control the camera state either free cam or static
	{
		camerastate = camerastate + 1;
		if (camerastate > 1)
		{
			camerastate = 0;
		}
		input->setKeyUp('f');
		input->setKeyUp('F');
	}

	if (input->isKeyDown('q') || input->isKeyDown('Q')) // This is to control the speed of the models that rotate
	{
		speed -= 1.0f;

		if (speed <= 0.0f)
		{
			speed = 1.0f;
		}
		input->setKeyUp('q');
		input->setKeyUp('Q');
	}

	if (input->isKeyDown('e') || input->isKeyDown('E')) // This is to control the speed of the models that rotate
	{
		speed += 1.0f;

		if (speed >= 400.0f)
		{
			speed = 399.0f;
		}
		input->setKeyUp('e');
		input->setKeyUp('E');
	}
	
	if (input->isKeyDown('r') || input->isKeyDown('R')) // Turns on wireframe mode
	{
		if (rstate == false)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			rstate = true;
			input->setKeyUp('r');
			input->setKeyUp('R');
			return;
		}

		if (rstate == true)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			rstate = false;
			input->setKeyUp('r');
			input->setKeyUp('R');
			return;
		}
	}

	if (camerastate == 0)
	{
		if (posState == 0)
		{
			camera.SetPosition(); // Sets the camera back to it's original position
			posState = 1;
		}
		camera.handleInput(dt);
	}
	else
	{
		// Handles the static camera 
		if (camPos == 0)
		{
			camera.cams(1);
		}

		if (camPos == 1)
		{
			camera.cams(2);
		}
		
		if (camPos == 2)
		{
			camera.cams(3);
		}

		if (camPos == 3)
		{
			camera.cams(4);
		}

	
		if (input->isKeyDown('1'))
		{
			camPos = 0;
			input->setKeyUp('1');
		}

		if (input->isKeyDown('2'))
		{
			camPos = 1;
			input->setKeyUp('2');
		}

		if (input->isKeyDown('3'))
		{
			camPos = 2;
			input->setKeyUp('3');
		}

		if (input->isKeyDown('4'))
		{
			camPos = 3;
			input->setKeyUp('4');
		}
		posState = 0;
	}
}

void Scene::update(float dt)
{
	// update scene related variables.
	camera.update(dt);
	angle += speed * dt; 
	lightangle += 10 * dt;
	// Calculate FPS for output
	calculateFPS();
}

void Scene::render_pillars()
{
	// 1 - Red procedurally generated sphere
	glPushMatrix();
		glTranslatef(-0.3, -0.07, 6);
		glScalef(0.03, 0.03, 0.03);
		glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
		geometry.render_stand();
	glPopMatrix();

	// Sets the material of the red sphere and renders it
	glPushMatrix();
		glTranslatef(-0.3, -0.01, 6);
		glScalef(0.03, 0.03, 0.03);
		glDisable(GL_COLOR_MATERIAL);
		GLfloat mat_diff_red[] = { 0.3, 0.0, 0.0, 1.0 };
		GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat high_shininess = 100;
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_red);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMateriali(GL_FRONT, GL_SHININESS, high_shininess);
		geometry.render_sphere();
		glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();
	
	// Renders lamp above 
	glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-0.3, 0.05, 6);
		glScalef(0.005, 0.005, 0.005);
		lamp.render();
	glPopMatrix();
	
	light.spotlight();

	// 2 - Models with reflections
	glPushMatrix();
		glTranslatef(-0.3, -0.07, 6.3);
		glScalef(0.03, 0.03, 0.03);
		glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
		geometry.render_stand();
	glPopMatrix();
	
	// Renders lamp above 
	glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-0.3, 0.05, 6.3);
		glScalef(0.005, 0.005, 0.005);
		lamp.render();
	glPopMatrix();

	light.spotlight2();

	// 3 - Eyeball disc
	glPushMatrix();
		glTranslatef(-0.3, -0.07, 5.7);
		glScalef(0.03, 0.03, 0.03);
		glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
		geometry.render_stand();
	glPopMatrix();
	
	// Renders lamp above 
	glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-0.3, 0.05, 5.7);
		glScalef(0.005, 0.005, 0.005);
		lamp.render();
	glPopMatrix();

	light.spotlight3();

	// 4 - Transparent box with sniper
	glPushMatrix();
		glTranslatef(0, -0.07, 5.7);
		glScalef(0.03, 0.03, 0.03);
		glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
		geometry.render_stand();
	glPopMatrix();
	
	// Sniper model
	glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-0.008, -0.019, 5.7);
		glRotatef(90, 0, 1, 0);
		glScalef(0.00038, 0.00038, 0.00038);
		sniper.render();
	glPopMatrix();

	// Transparent glass
	glPushMatrix();
		glTranslatef(0, -0.019, 5.7);
		glScalef(0.025, 0.025, 0.025);
		glColor4f(0.3, 0.2, 0.6, 0.2); 
		glEnable(GL_BLEND);
		geometry.render_stand();
		glDisable(GL_BLEND);
	glPopMatrix();

	// 5 - Rotating light 
	glPushMatrix();
		glTranslatef(0, -0.07, 6.3);
		glScalef(0.03, 0.03, 0.03);
		glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
		geometry.render_stand();
	glPopMatrix();

	// Renders a light that rotates
	light.rotating(lightangle);
	
	// 6 - Teapot with shadow
	glPushMatrix();
		glTranslatef(0.3, -0.07, 6);
		glScalef(0.03, 0.03, 0.03);
		glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
		geometry.render_stand();
	glPopMatrix();
	
	Shadow(); // Renders teapot and it's shadow

	// Renders lamp above 
	glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(0.3, 0.05, 6);
		glScalef(0.005, 0.005, 0.005);
		lamp.render();
	glPopMatrix();
	
	// 7 - Solar System
	glPushMatrix();
		glTranslatef(0.3, -0.07, 5.7);
		glScalef(0.03, 0.03, 0.03);
		glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
		geometry.render_stand();
	glPopMatrix();

	// 8 - Yoda with different colour lighting
	glPushMatrix();
		glTranslatef(0.3, -0.07, 6.3);
		glScalef(0.03, 0.03, 0.03);
		glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
		geometry.render_stand();
	glPopMatrix();

	// Renders yoda model
	glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslatef(0.3, -0.06, 6.3);
		glRotatef(-135, 0, 1, 0);
		glScalef(0.20, 0.20, 0.20);
		yoda.render();
	glPopMatrix();

	// Renders lamp above 
	glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(0.3, 0.05, 6.3);
		glScalef(0.005, 0.005, 0.005);
		lamp.render();
	glPopMatrix();

	// Shines a light on yoda which changes on a key press
	light.colours(keystate);
}

void Scene::render_plane()
{
	// Renders a plane
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(1, 1, 1); 

	glNormal3f(0, 1, 0);
	glVertex3f(-1, 1, 1);

	glNormal3f(0, 1, 0);
	glVertex3f(-1, 1, -1);

	glNormal3f(0, 1, 0);
	glVertex3f(1, 1, -1);
	glEnd();
}

void Scene::reflected()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_ALWAYS, 1, 1);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glDisable(GL_DEPTH_TEST);
	
	glPushMatrix();
		glTranslatef(-0.3, -0.0699, 6.3);
		glScalef(0.03, 0.03, 0.03);
		render_plane();
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	// Floor Jinx
	glPushMatrix();
		glScalef(1.0, -1.0, 1.0);
		glTranslatef(-0.31, 0.04, 6.31);
		glRotatef(angle, 0, 1, 0);
		glScalef(0.00015, 0.00015, 0.00015);
		jinx.render();
	glPopMatrix();

	// Floor Leblanc
	glPushMatrix();
		glScalef(1.0, -1.0, 1.0);
		glTranslatef(-0.29, 0.04, 6.29);
		glRotatef(-angle, 0, 1, 0);
		glScalef(0.00015, 0.00015, 0.00015);
		leblanc.render();
	glPopMatrix();
	
	// Floor
	glDisable(GL_STENCIL_TEST);
	glEnable(GL_BLEND);
	glDisable(GL_LIGHTING);
	
	glPushMatrix();
		glColor4f(0.8f, 0.8f, 1.0f, 0.8f);
		glTranslatef(-0.3, -0.0699, 6.3);
		glScalef(0.03, 0.03, 0.03);
		render_plane();
	glPopMatrix();
	
	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);

	// Jinx
	glPushMatrix();
		glTranslatef(-0.31, -0.04, 6.31);
		glRotatef(angle, 0, 1, 0);
		glScalef(0.00015, 0.00015, 0.00015);
		jinx.render();
	glPopMatrix();

	// Leblanc
	glPushMatrix();
		glTranslatef(-0.29, -0.04, 6.29);
		glRotatef(-angle, 0, 1, 0);
		glScalef(0.00015, 0.00015, 0.00015);
		leblanc.render();
	glPopMatrix();
}

void Scene::solarSystem()
{
	light.sunlight(); // Sunlight
	geometry.solarSystem(); // Solar system
}

void Scene::disc()
{
	// Renders disc
	glPushMatrix();
		glTranslatef(-0.3, -0.038, 5.7);
		glRotatef(90, 1, 0, 0);
		glScalef(0.03, 0.03, 0.03);
		geometry.render_disc(eyeball);
	glPopMatrix();
}

void Scene::Shadow()
{
	GLfloat floorVerts[] = { -1.f, -0.038f, -1.f, //top left
							 -1.f, -0.038f, 1.f,  // bottom left
							 1.f, -0.038f, 1.f,   //bottom right
							 1.f, -0.038f, -1.f };// top right

	float shadowMatrix[16];
	GLfloat Light_Position[] = { 0.3f, 0.09f, 6.0f, 1.0f };
	light.shadow();
	shadow.generateShadowMatrix(shadowMatrix, Light_Position, floorVerts); // Generate shadow matrix
	glPushMatrix();
		glTranslatef(0.3, -0.07, 6);
		glScalef(0.03, 0.03, 0.03);
		render_plane(); // Render plane
	glPopMatrix();

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glColor3f(0.1f, 0.1f, 0.1f); // Shadow's colour

	// Render teapot shadow
	glPushMatrix();
		glMultMatrixf((GLfloat*)shadowMatrix); //translate to floor and draw shadow, remember to match any transforms on the object
		glTranslatef(0.3, -0.5, 6);
		glRotatef(angle, 0, 1, 0);
		glScalef(0.0063f, 0.0063f, 0.0063f);
		teapot.render();
	glPopMatrix();

	glColor3f(1.0f, 1.0f, 1.0f); // Reset colour
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	// Render teapot above shadow
	glPushMatrix();
		glTranslatef(0.3, -0.020, 6);
		glRotatef(angle, 0, 1, 0);
		glScalef(0.0015f, 0.0015f, 0.0015f);
		teapot.render();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void Scene::render() 
{
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt
	(
		camera.Position().x,
		camera.Position().y,
		camera.Position().z,
		camera.LookAt().x,
		camera.LookAt().y,
		camera.LookAt().z,
		camera.Up().x,
		camera.Up().y,
		camera.Up().z);
	
	// Render geometry/scene here -------------------------------------
	
	// Skybox
	glPushMatrix();
		glTranslatef(0, 0.4, 0);
		skybox.render();
	glPopMatrix();
	
	reflected(); // Renders models which have reflections
	solarSystem(); // Solar system 
	geometry.spheres(); // Renders the spheres
	render_pillars(); // Renders all the pillars needed
	
	disc(); // Textured disc
	
	// End render geometry --------------------------------------

	// Render text, should be last object rendered.
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	renderTextOutput();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

void Scene::initialiseOpenGL()
{
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h) 
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

// Calculates FPS
void Scene::calculateFPS()
{
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	sprintf_s(camMode, "Use F to change the camera mode" );
	sprintf_s(modelSpeed, "Use Q or E to change the models speed");
	sprintf_s(wireframe, "Press R to turn on wireframe mode");
	sprintf_s(spacebar, "Press Space to change Yoda's light");
	sprintf_s(staticCam, "Press 1, 2, 3 or 4 to change camera");
	displayText(-1.f, 0.96f, 1.f, 1.f, 1.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 1.f, 1.f, fps);
	displayText(-1.f, 0.84f, 1.f, 1.f, 1.f, camMode);
	displayText(-1.f, 0.78f, 1.f, 1.f, 1.f, modelSpeed);
	displayText(-1.f, 0.72f, 1.f, 1.f, 1.f, wireframe);
	displayText(-1.f, 0.66f, 1.f, 1.f, 1.f, spacebar);

	if (camerastate == 1)
	{
		displayText(-1.f, 0.60f, 1.f, 1.f, 1.f, staticCam);
	}
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}
