#include "Geometry.h"

extern GLfloat vertices[] = { -1.0f, -1.0f, 1.0f,
							 1.0f, -1.0f, 1.0f,
							 1.0f, 1.0f, 1.0f,
							-1.0f, 1.0f, 1.0f,
							-1.0f, 1.0f, -1.0f,
							 1.0f, 1.0f, -1.0f,
							 1.0f, -1.0f, -1.0f,
							-1.0f, -1.0f, -1.0f,
							 1.0f, -1.0f, 1.0f,
							 1.0f, -1.0f, -1.0f,
							 1.0f, 1.0f, -1.0f,
							 1.0f, 1.0f, 1.0f,
							-1.0f, -1.0f, -1.0f,
							-1.0f, -1.0f, 1.0f,
							-1.0f, 1.0f, 1.0f,
							-1.0f, 1.0f, -1.0f };

extern float cube_norms[] = { 0.0, 0.0, 1.0, //0
							  0.0, 0.0, 1.0,  //1
							  0.0, 0.0, 1.0,  //2
							  0.0, 0.0, 1.0,   //3
							  0.0, 0.0, 1.0, //4
							  0.0, 0.0, 1.0, // 5
							  0.0, 0.0, 1.0 }; //6

extern GLubyte cubeIndices[24] = { 0,1,2,3, 4,5,6,7, 3,2,5,4, 7,6,1,0,
								 8,9,10,11, 12,13,14,15 };

void Geometry::render_stand()
{
	// Step 1
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	// Step 2
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glNormalPointer(GL_FLOAT, 0, cube_norms);

	//Step 3
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);

	// Step 4
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void Geometry::render_sphere()
{
	float theta = 0;
	float delta = 0;
	float segments = 100; // How much segments the sphere should have
	
	float tInterval = (2 * 3.14) / segments; // Latitude
	float dInterval = 3.14 / segments; // Longitude

	glBegin(GL_QUADS);
	for (int i = 0; i < segments; i++)
	{
		for (int j = 0; j < segments; j++)
		{
			//[x][y] 
			glNormal3f(((cos(theta)) * sin(delta)), cos(delta), sin(theta) * sin(delta));
			glVertex3f(((cos(theta)) * sin(delta)), cos(delta), sin(theta) * sin(delta)); // bottom left

			//[x+1][y]
			glNormal3f(((cos(theta + tInterval)) * sin(delta)), cos(delta), sin(theta + tInterval) * sin(delta));
			glVertex3f(((cos(theta + tInterval)) * sin(delta)), cos(delta), sin(theta + tInterval) * sin(delta)); // bottom right

			//[x+1][y+1]
			glNormal3f(((cos(theta + tInterval)) * sin(delta + dInterval)), cos(delta + dInterval), sin(theta + tInterval) * sin(delta + dInterval));
			glVertex3f(((cos(theta + tInterval)) * sin(delta + dInterval)), cos(delta + dInterval), sin(theta + tInterval) * sin(delta + dInterval)); // top right

			//[x][y+1]
			glNormal3f(((cos(theta)) * sin(delta + dInterval)), cos(delta + dInterval), sin(theta) * sin(delta + dInterval));
			glVertex3f(((cos(theta)) * sin(delta + dInterval)), cos(delta + dInterval), sin(theta) * sin(delta + dInterval)); // top left
			theta += tInterval;
		}
		delta += dInterval;
	}
	glDisable(GL_TEXTURE_2D);
	glEnd();
}

void Geometry::render_disc(GLuint texture)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	float theta = 0;
	float r = 1; // radius
	float d = r * 2; // diameter
	float segments = 100; // how much segments / triangles make up the disc
	float interval = (2 * 3.14) / segments;
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < segments; i++)
	{
		glNormal3f(0, 1, 0); 
		glTexCoord2f(0.5, 0.5);
		glVertex3f(0, 0, 0);

		glNormal3f(0, 1, 0);
		glTexCoord2f((cos(theta) / d) + 0.5, (sin(theta) / d) + 0.5);
		glVertex3f(r * cos(theta), r * sin(theta), 0);

		theta += interval;
		glNormal3f(0, 1, 0);
		glTexCoord2f((cos(theta) / d) + 0.5, (sin(theta) / d) + 0.5);
		glVertex3f(r * cos(theta), r * sin(theta), 0);

	}
	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);
	glEnd();
}

void Geometry::solarSystem()
{
	glPushMatrix();
		// Materials
		glDisable(GL_COLOR_MATERIAL);
		GLfloat mat_diff_green[] = { 0.0, 0.6, 0.1, 1.0 };
		GLfloat mat_diff_purple[] = { 0.4, 0.0, 0.7, 1.0 };
		GLfloat mat_diff_blue[] = { 0.1, 0.5, 0.8, 1.0 };
		GLfloat mat_diff_grey[] = { 0.4, 0.4, 0.4, 1.0 };
		GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat high_shininess = 100;

		// Sun
		glPushMatrix();
			glTranslatef(0.3, 0.0, 5.7);
			glScalef(0.04, 0.04, 0.04);
			glDisable(GL_LIGHTING);
			glColor3f(1, 1, 0);
			gluSphere(gluNewQuadric(), 0.5, 40, 40);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		// Planet 1 - Blue
		glPushMatrix();
			glTranslatef(0.27, 0.0, 5.65);
			glScalef(0.03, 0.03, 0.03);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_blue);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMateriali(GL_FRONT, GL_SHININESS, high_shininess);
			gluSphere(gluNewQuadric(), 0.5, 40, 40);
		glPopMatrix();

		// Planet 2 - Purple
		glPushMatrix();
			glTranslatef(0.3, 0.05, 5.7);
			glScalef(0.025, 0.025, 0.025);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_purple);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMateriali(GL_FRONT, GL_SHININESS, high_shininess);
			gluSphere(gluNewQuadric(), 0.5, 40, 40);
		glPopMatrix();

		// Planet 3 - Green
		glPushMatrix();
			glTranslatef(0.35, 0.0, 5.7);
			glScalef(0.025, 0.025, 0.025);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_green);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMateriali(GL_FRONT, GL_SHININESS, high_shininess);
			gluSphere(gluNewQuadric(), 0.5, 40, 40);
		glPopMatrix();

		// Planet 4 - Grey
		glPushMatrix();
			glTranslatef(0.25, 0.0, 5.7);
			glScalef(0.023, 0.023, 0.023);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_grey);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMateriali(GL_FRONT, GL_SHININESS, high_shininess);
			gluSphere(gluNewQuadric(), 0.5, 40, 40);
		glPopMatrix();
		glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();
}

void Geometry::spheres()
{
	// Renders 9 pink spheres
	glPushMatrix();
		glDisable(GL_COLOR_MATERIAL);
		GLfloat mat_diff_pink[] = { 1, 0.0, 0.5, 1.0 };
		GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat high_shininess = 100;
		glPushMatrix();
			glTranslatef(0, 0, 6.3);
			glScalef(0.02, 0.02, 0.02);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_pink);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMateriali(GL_FRONT, GL_SHININESS, high_shininess);
			gluSphere(gluNewQuadric(), 0.5, 40, 40);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, 0, 6.32);
			glScalef(0.02, 0.02, 0.02);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_pink);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMateriali(GL_FRONT, GL_SHININESS, high_shininess);
			gluSphere(gluNewQuadric(), 0.5, 40, 40);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, 0, 6.28);
			glScalef(0.02, 0.02, 0.02);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_pink);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMateriali(GL_FRONT, GL_SHININESS, high_shininess);
			gluSphere(gluNewQuadric(), 0.5, 40, 40);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-0.02, 0, 6.3);
			glScalef(0.02, 0.02, 0.02);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_pink);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMateriali(GL_FRONT, GL_SHININESS, high_shininess);
			gluSphere(gluNewQuadric(), 0.5, 40, 40);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-0.02, 0, 6.32);
			glScalef(0.02, 0.02, 0.02);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_pink);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMateriali(GL_FRONT, GL_SHININESS, high_shininess);
			gluSphere(gluNewQuadric(), 0.5, 40, 40);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-0.02, 0, 6.28);
			glScalef(0.02, 0.02, 0.02);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_pink);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMateriali(GL_FRONT, GL_SHININESS, high_shininess);
			gluSphere(gluNewQuadric(), 0.5, 40, 40);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.02, 0, 6.3);
			glScalef(0.02, 0.02, 0.02);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_pink);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMateriali(GL_FRONT, GL_SHININESS, high_shininess);
			gluSphere(gluNewQuadric(), 0.5, 40, 40);
		glPopMatrix();
	
		glPushMatrix();
			glTranslatef(0.02, 0, 6.32);
			glScalef(0.02, 0.02, 0.02);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_pink);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMateriali(GL_FRONT, GL_SHININESS, high_shininess);
			gluSphere(gluNewQuadric(), 0.5, 40, 40);
		glPopMatrix();
	
		glPushMatrix();
			glTranslatef(0.02, 0, 6.28);
			glScalef(0.02, 0.02, 0.02);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_pink);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMateriali(GL_FRONT, GL_SHININESS, high_shininess);
			gluSphere(gluNewQuadric(), 0.5, 40, 40);
		glPopMatrix();
		glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();
}