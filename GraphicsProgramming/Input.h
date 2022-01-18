// Input class
// Stores current keyboard and mouse state include, pressed keys, mouse button pressed and mouse position.
// @author Paul Robertson
#ifndef INPUT_H
#define INPUT_H

class Input
{
	// Mouse struct stores mouse related data include cursor
	// x, y coordinates and left/right button pressed state.
	struct Mouse
	{
		int x,y;
		bool left, right;
	};

public:
	Input();
	// Getters and setters for keys
	void setKeyDown(unsigned char key);
	void setKeyUp(unsigned char key);
	bool isKeyDown(int key);

	// getters and setters for mouse buttons and position.
	void setMouseX(int lx);
	void setMouseY(int ly);
	void setMousePos(int x, int y);
	int getMouseX();
	int getMouseY();
	void setMouseLDown(bool b);
	bool isMouseLDown();
	void setMouseRDown(bool down);
	bool isMouseRDown();

private:
	// Boolean array, element per key
	// Mouse struct object.
	bool keys[256]{ false };
	Mouse mouse;

};

#endif