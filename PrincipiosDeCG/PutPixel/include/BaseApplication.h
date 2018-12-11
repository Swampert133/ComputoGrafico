#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <iostream>
#include "Object3D.h"
#include <stack>
#include "GLFW\glfw3.h"

class Color
{
private:
	char color[4];

public:
	char R() { return color[0]; };
	char G() { return color[1]; };
	char B() { return color[2]; };
	char A() { return color[3]; };

	void R(const char& c) { color[0] = c; };
	void G(const char& c) { color[1] = c; };
	void B(const char& c) { color[2] = c; };
	void A(const char& c) { color[3] = c; };
};

class BaseApplication {
public:

	static const int WIDTH = 1024;
	static const int HEIGHT = 1024;
	static const int RGB = 3;
	static const int RGBA = 4;

	BaseApplication();
	~BaseApplication();

	void init();
	void display();
	void reshape(int w, int h);
	void swapbuffers();
	void cursor_position(double xpos, double ypos);
	void putPixel(GLubyte *buffer, const int& x, const int& y, const char& R, const char& G, const char& B, const char& A);
	void putPixel(const int& x, const int& y, const char& R, const char& G, const char& B, const char& A);
	void putPixel(const int& x, const int& y, Color c);

	std::stack<glm::mat4> mStack;
	glm::mat4 mProjectionMatrix, mTransform;
	glm::vec3 vEye;
	GLFWwindow* window;
	unsigned char Buffers[2][WIDTH*HEIGHT*RGBA];


private:	
	GLuint texturesID[2], pboID[2];
	GLuint shaderID;
	GLuint VAO, VBO;
	GLuint sampler;
	GLuint uTransform;
	GLubyte* _screenBuffer;
	int _currentBuffer, 
		_nextBuffer;

	glm::vec3 myLightPosition;
	GLuint uMyLightPosition[2];	

	float fTime;
	void initTextures();
	void processPBO();
	void initPBOs();
	int _drawMode,
		shader;
	bool moveLight;
	void fakeBuffers();

public:
	//this functions sould be reimplemented
	virtual void setup();
	virtual void update();
	virtual void draw();
	virtual void keyboard(int key, int scancode, int action, int mods);
};

#endif //__APPLICATION_H__