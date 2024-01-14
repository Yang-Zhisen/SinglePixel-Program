#pragma once
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<string>

class ShowImage
{
public:
	int wide = 300;//屏宽
	int height = 200;//屏高


	ShowImage();
	~ShowImage();

	bool Input();

	void ObjInit();

	void ShaderInit();

	void Getbuffer(const char* vertexpath, const char* fragmentpath);

	void DrawStride(float* fx);

private:
	GLFWwindow* window = NULL;
	int Monitor;//获取监视器数量
	GLFWmonitor** getMonitors;


//-----Obj的初始化

	unsigned int vbo;
	unsigned int vao;
	unsigned int ebo;

	GLfloat vertices[12] = {
-1.0f, 1.0f,0.0f,
-1.0f,-1.0f,0.0f,
 1.0f,-1.0f,0.0f,
 1.0f, 1.0f,0.0f
	};//屏幕各个顶点 由两个三角形绘制
	GLuint indices[6] =
	{ 0,1,2,
	2,3,0 };//俩三角形的绘制顺序

//------Shader初始化
	unsigned int id;
	const char* vertexsource ;
	const char* fragmentsource ;
	std::string vertexstring;
	std::string fragmentstring;

	unsigned int vertex;
	unsigned int fragment;

	void Checkererrors(unsigned int ID, std::string type);
//------绘制初始化
	void DrawInit();

};

