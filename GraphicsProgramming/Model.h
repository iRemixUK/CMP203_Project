// Model class, represents a loaded OBJ model
// handles the loading/processing of the model file. Also loads and stores its own texture
// NOT complete, for students to complete. Model data requires being sorted and the render function needs completed.
#ifndef _MODEL_H_
#define _MODEL_H_

// INCLUDES //
#include <glut.h>
#include <fstream>
#include <gl/gl.h>
#include <gl/glu.h>

using namespace std;

// MY CLASS INCLUDES //
#include <vector>
#include "Vector3.h"
#include "SOIL.h"

class Model
{

public:
	bool load(char* modelFilename, char* textureFilename);
	void render();

private:

	void loadTexture(char*);
	bool loadModel(char*);

	// model texture
	GLuint texture;

	// Storage for sorted data
	vector<float> vertex, normals, texCoords;

};

#endif