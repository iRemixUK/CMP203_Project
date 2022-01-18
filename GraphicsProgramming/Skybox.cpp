#include "Skybox.h"
Skybox::Skybox()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	skybox = SOIL_load_OGL_texture(
		"gfx/galaxy.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
}

void Skybox::drawSkybox()
{
	glPushMatrix(); 
		glBindTexture(GL_TEXTURE_2D, skybox); // Tells opengl which texture to use
		glTranslatef(0, 0, 6);
		glBegin(GL_QUADS); // Begin drawing state

		// Back face 
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.75f, 0.35f);
		glVertex3f(0.5f, 0.5f, 0.5f); // Top right

		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.75f, 0.66f);
		glVertex3f(0.5f, -0.5f, 0.5f); // Bottom right

		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(1.0f, 0.66f);
		glVertex3f(-0.5f, -0.5f, 0.5f); // Bottom left

		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(1.0f, 0.35f);
		glVertex3f(-0.5f, 0.5f, 0.5f); // Top left

		// Front face
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.50f, 0.33f);
		glVertex3f(0.5f, 0.5f, -0.5f); // Top right

		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.50f, 0.66f);
		glVertex3f(0.5f, -0.5f, -0.5f); // Bottom right

		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.25f, 0.66f);
		glVertex3f(-0.5f, -0.5f, -0.5f); // Bottom right

		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.25f, 0.33f);
		glVertex3f(-0.5f, 0.5f, -0.5f); // Top left

		// Right Face 
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.50f, 0.35f);
		glVertex3f(0.5f, 0.5f, -0.5f); // Top left

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.50f, 0.66f);
		glVertex3f(0.5f, -0.5f, -0.5f); // Bottom Left

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.75F, 0.66f);
		glVertex3f(0.5f, -0.5f, 0.5f); // Bottom right

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.75f, 0.35f);
		glVertex3f(0.5f, 0.5f, 0.5f); // Top right

		//Left face 
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.35f);
		glVertex3f(-0.5f, 0.5f, 0.5f); // Top left

		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.66f);
		glVertex3f(-0.5f, -0.5f, 0.5f); // Bottom Left

		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.25F, 0.66f);
		glVertex3f(-0.5f, -0.5f, -0.5f); // Bottom right

		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.25f, 0.35f);
		glVertex3f(-0.5f, 0.5f, -0.5f); // Top right

		//Top Face 
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.33f);
		glVertex3f(-0.5f, 0.5f, -0.5f); // Top left

		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f); // Bottom Left

		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.50f, 0.0f);
		glVertex3f(0.5f, 0.5f, 0.5f); // Bottom Right

		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.50f, 0.33f);
		glVertex3f(0.5f, 0.5f, -0.5f); // Top right

		glBindTexture(GL_TEXTURE_2D, NULL); //Tells opengl which texture to use
		
		// Render bottom face 
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f); //	Top left

		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, -0.5f); // Bottom left

		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.5f); // Bottom right

		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f); // Top Right

		glEnd(); 
	glPopMatrix();
}

void Skybox::render()
{
	drawSkybox();
}

Skybox::~Skybox()
{

}
