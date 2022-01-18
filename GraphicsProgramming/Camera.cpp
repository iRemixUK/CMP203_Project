#include "Camera.h"

Camera::Camera()
{
	Yaw = 0.0f;
	Pitch = 0.0f;
	Roll = 0.0f;
	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 6.0f;
	width = glutGet(GLUT_WINDOW_WIDTH);
	height = glutGet(GLUT_WINDOW_HEIGHT);
	glutSetCursor(GLUT_CURSOR_NONE); // Hide the cursor
	mouseX = 0.f;
	mouseY = 0.f;
	glutWarpPointer(width / 2, height / 2); // Set the mouse to the center of the screen
}

void Camera::handleInput(float dt)
{
	//Keyboard stuff
	if (input->isKeyDown('w') || input->isKeyDown('W')) // Move Forward
	{
		forward.scale(dt);
		position += forward;
	}

	if (input->isKeyDown('s') || input->isKeyDown('S')) // Move Backwards
	{
		forward.scale(dt);
		position -= forward;
	}

	if (input->isKeyDown('a') || input->isKeyDown('A')) // Move Left
	{
		right.scale(dt);
		position -= right;
	}

	if (input->isKeyDown('d') || input->isKeyDown('D')) // Move Right
	{
		right.scale(dt);
		position += right;
	}

	//Mouse stuff
	glutWarpPointer(width / 2, height / 2);
	elapsedTime += dt; // Function to skip one second so the calculations will be done on the correct position of the mouse
	if (elapsedTime >= 1)
	{
		if (input->getMouseX() != 0 || input->getMouseY() != 0)
		{
			mouseX = input->getMouseX() - width / 2;
			mouseY = input->getMouseY() - height / 2;
		}

		if (mouseX != 0)
		{
			Yaw += mouseX * dt * 5;
			glutWarpPointer(width / 2, height / 2);
		}

		if (mouseY != 0) // Rotate right
		{
			Pitch -= mouseY * dt * 5;
			glutWarpPointer(width / 2, height / 2);
		}
	}
	Lookat = forward + position; 
}

void Camera::cams(int keystate)
{
	// Set these values to zero so the free camera doesn't affect the static camera
	Yaw = 0.0f;
	Pitch = 0.0f;
	Roll = 0.0f;

	Lookat = Vector3(0, 0, 6);

	if (keystate == 1)
	{
		position = Vector3(-0.47, 0.75, 6.45);
		up = Vector3(0, 1, 0);
	}
	
	if (keystate == 2)
	{
		position = Vector3(-0.47, 0.75, 5.57);
		up = Vector3(0, 1, 0);
	}

	if (keystate == 3)
	{
		position = Vector3(0.47, 0.75, 5.57);
		up = Vector3(0, 1, 0);
	}

	if (keystate == 4)
	{
		position = Vector3(0.47, 0.75, 6.45);
		up = Vector3(0, 1, 0);
	}
}

Vector3 Camera::Position()
{
	return position;
}

Vector3 Camera::LookAt()
{
	return Lookat;
}

Vector3 Camera::Up()
{
	return up;
}

void Camera::SetPosition()
{
	position = Vector3(0, 0, 6.35);
}

void Camera::update(float dt)
{
	glutWarpPointer(width / 2, height / 2);
	float cosR, cosP, cosY;//temp values for sin/cos from 
	float sinR, sinP, sinY; // Roll, Pitch and Yaw are variables stored by the camera
	// handle rotation
	// Only want to calculate these values once, when rotation changes, not every frame.
	cosY = cosf(Yaw * 3.1415 / 180);
	cosP = cosf(Pitch * 3.1415 / 180);
	cosR = cosf(Roll * 3.1415 / 180);
	sinY = sinf(Yaw * 3.1415 / 180);
	sinP = sinf(Pitch * 3.1415 / 180);
	sinR = sinf(Roll * 3.1415 / 180);

	//This using the parametric equation of a sphere
	// Calculate the three vectors to put into  gluLookat
	// Look direction,  position and the up vector 
	// This function could also calculate the right vector
	forward.x = sinY * cosP;
	forward.y = sinP;
	forward.z = cosP * -cosY;

	// Look At Point// To calculate add Forward Vector to Camera position.
	// Up Vector
	up.x = -cosY * sinR - sinY * sinP * cosR;
	up.y = cosP * cosR;
	up.z = -sinY * sinR - sinP * cosR * -cosY;

	// Side Vector (right)
	// this is a cross product between the forward and up vector.
	// If you don’t need to calculate this,  don’t do it
	right = forward.cross(up);
	
	// Makes sure the camera doesn't leave the skybox
	if (position.x <= -0.50)
	{
		position.x = -0.45;
		Lookat = Vector3(position.x, position.y, position.z);
	}

	if (position.x >= 0.50)
	{
		position.x = 0.45;
		Lookat = Vector3(position.x, position.y, position.z);
	}

	if (position.y <= -0.03)
	{
		position.y = 0.0;
		Lookat = Vector3(position.x, position.y, position.z);
	}

	if (position.y >= 0.78)
	{
		position.y = 0.77;
		Lookat = Vector3(position.x, position.y, position.z);
	}
	
	if (position.z >= 6.45)
	{
		position.z = 6.44;
		Lookat = Vector3(position.x, position.y, position.z);
	}

	if (position.z <= 5.54)
	{
		position.z = 5.55;
		Lookat = Vector3(position.x, position.y, position.z);
	}
}

Camera::~Camera()
{

}