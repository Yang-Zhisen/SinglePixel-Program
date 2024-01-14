#pragma once
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<string>

class ShowImage
{
public:
	int wide = 400;//����
	int height = 300;//����


	ShowImage();
	~ShowImage();

	bool Input();

	void ObjInit();

	void ShaderInit();

	void Getbuffer(const char* vertexpath, const char* fragmentpath);

	void DrawStride(float* fx);

private:
	GLFWwindow* window = NULL;
	int Monitor;//��ȡ����������


//-----Obj�ĳ�ʼ��

	unsigned int vbo;
	unsigned int vao;
	unsigned int ebo;

	GLfloat vertices[12] = {
-1.0f, 1.0f,0.0f,
-1.0f,-1.0f,0.0f,
 1.0f,-1.0f,0.0f,
 1.0f, 1.0f,0.0f
	};//��Ļ�������� �����������λ���
	GLuint indices[6] =
	{ 0,1,2,
	2,3,0 };//�������εĻ���˳��

//------Shader��ʼ��
	unsigned int id;
	const char* vertexsource ;
	const char* fragmentsource ;
	std::string vertexstring;
	std::string fragmentstring;

	unsigned int vertex;
	unsigned int fragment;
	GLFWmonitor** getMonitors;

	void Checkererrors(unsigned int ID, std::string type);
//------���Ƴ�ʼ��
	void DrawInit();

};

