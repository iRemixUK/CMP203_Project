#include "Light.h"

void Light::spotlight()
{
		glPushMatrix();
		glDisable(GL_COLOR_MATERIAL);
		GLfloat Light_Ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
		GLfloat Light_Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat Light_Position[] = { -0.3f, 0.09f, 6.0f, 1.0f };
		GLfloat spot_Direction[] = { 0.0f, -1.0f, 0.0f };

		glLightfv(GL_LIGHT1, GL_AMBIENT, Light_Ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, Light_Diffuse);
		glLightfv(GL_LIGHT1, GL_POSITION, Light_Position);
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0f);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_Direction);
		glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 50.0);
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0); 
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.25); 
		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0);
		glEnable(GL_LIGHT1);
		glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();
}

void Light::spotlight2()
{
	glPushMatrix();
		glDisable(GL_COLOR_MATERIAL);
		GLfloat Light_Ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
		GLfloat Light_Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat Light_Position[] = { -0.3f, 0.09f, 6.3f, 1.0f };
		GLfloat spot_Direction[] = { 0.0f, -1.0f, 0.0f };

		glLightfv(GL_LIGHT2, GL_AMBIENT, Light_Ambient);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, Light_Diffuse);
		glLightfv(GL_LIGHT2, GL_POSITION, Light_Position);
		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45.0f);
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_Direction);
		glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 50.0);
		glEnable(GL_LIGHT2);
		glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();
}

void Light::spotlight3()
{
	glPushMatrix();
		glDisable(GL_COLOR_MATERIAL);
		GLfloat Light_Ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
		GLfloat Light_Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat Light_Position[] = { -0.3f, 0.09f, 5.7f, 1.0f };
		GLfloat spot_Direction[] = { 0.0f, -1.0f, 0.0f };

		glLightfv(GL_LIGHT3, GL_AMBIENT, Light_Ambient);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, Light_Diffuse);
		glLightfv(GL_LIGHT3, GL_POSITION, Light_Position);
		glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 45.0f);
		glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_Direction);
		glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 50.0);
		glEnable(GL_LIGHT3);
		glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();
}

void Light::sunlight()
{
	glPushMatrix();
		GLfloat Light_Diffuse[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		GLfloat Light_Position[] = { 0.3, 0.0, 5.7, 1.0f };

		glLightfv(GL_LIGHT4, GL_DIFFUSE, Light_Diffuse);
		glLightfv(GL_LIGHT4, GL_POSITION, Light_Position);
		glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 10);
		glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, 10);
		glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 10);
		glEnable(GL_LIGHT4);
	glPopMatrix();
}

void Light::rotating(float angle)
{
	glPushMatrix();
		glRotatef(angle * 2, 0, 0, 1);
		GLfloat Light_Diffuse[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		GLfloat Light_Position[] = { 0, 0.15, 6.3, 1.0f };
		GLfloat spot_Direction[] = { 0.0f, -1.0f, 0.0f };

		glLightfv(GL_LIGHT5, GL_DIFFUSE, Light_Diffuse);
		glLightfv(GL_LIGHT5, GL_POSITION, Light_Position);
		glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 45.0f);
		glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, spot_Direction);
		glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 100.0);
		glEnable(GL_LIGHT5);
	glPopMatrix();
}

void Light::shadow()
{
	glPushMatrix();
		glDisable(GL_COLOR_MATERIAL);
		GLfloat Light_Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat Light_Position[] = { 0.3f, 0.09f, 6.0f, 1.0f };
		GLfloat spot_Direction[] = { 0.0f, -1.0f, 0.0f };

		glLightfv(GL_LIGHT6, GL_DIFFUSE, Light_Diffuse);
		glLightfv(GL_LIGHT6, GL_POSITION, Light_Position);
		glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, 45.0f);
		glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, spot_Direction);
		glLightf(GL_LIGHT6, GL_SPOT_EXPONENT, 50.0);
		glEnable(GL_LIGHT6);
		glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();
}

void Light::colours(int keystate)
{
	// Changes the colour of the light depending on key presses
	if (keystate == 0)
	{
		// White light
		r = 1;
		g = 1;
		b = 1;
	}

	if (keystate == 1)
	{
		// Red light
		r = 1;
		g = 0;
		b = 0;
	}

	if (keystate == 2)
	{
		// Green light
		r = 0;
		g = 1;
		b = 0;
	}

	if (keystate == 3)
	{
		// Blue light
		r = 0;
		g = 0;
		b = 1;
	}

	glPushMatrix();
		GLfloat Light_Diffuse[] = { r, g, b, 1.0f };
		GLfloat Light_Position[] = { 0.3f, 0.09f, 6.3f, 1.0f };
		GLfloat spot_Direction[] = { 0.0f, -1.0f, 0.0f };

		glLightfv(GL_LIGHT7, GL_DIFFUSE, Light_Diffuse);
		glLightfv(GL_LIGHT7, GL_POSITION, Light_Position);
		glLightf(GL_LIGHT7, GL_SPOT_CUTOFF, 45.0f);
		glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, spot_Direction);
		glLightf(GL_LIGHT7, GL_SPOT_EXPONENT, 50.0);
		glEnable(GL_LIGHT7);
	glPopMatrix();
}