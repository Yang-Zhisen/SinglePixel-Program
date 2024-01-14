#pragma once
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include <sstream>
#include<string>
#include "ShowStripe.h"

ShowImage::ShowImage()
{
	//����Opengl��ʼ��
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//�κ�OpenGL��չʾ����Ҫ���ڣ���˴��ڴ���ֱ���ڳ�ʼ���н���
	getMonitors= glfwGetMonitors(&Monitor);
	window = glfwCreateWindow(wide, height, "test window", getMonitors[0], NULL);

	if (window == NULL)
	{
		std::cout << "�򿪴���" << std::endl;
		glfwTerminate();//��ֹ
		return ;
	}
	glfwMakeContextCurrent(window);
	glViewport(wide/4, height/4, wide, height);
	glewInit();

}

bool ShowImage::Input()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
		return true;
	}
	else
		return false;
}

void ShowImage::ObjInit() {
	//�� vao,vbo,ebo ��������
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//���ⵢ��һ�죬����������Ҫ������-----------------------------------
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}


void ShowImage::ShaderInit()
{
	//����ɫ�����г�ʼ������
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexsource, NULL);
	glCompileShader(vertex);
	Checkererrors(vertex, "Vertex");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentsource, NULL);
	glCompileShader(fragment);
	Checkererrors(fragment, "Fragment");


	//��һֱʹ�ã��ͽ���ɫ���ڴ����Ӳ�����
	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);

}

void ShowImage::Getbuffer(const char* vertexpath, const char* fragmentpath)
{
	std::ifstream vertexfile;
	std::ifstream fragmentfile;
	std::stringstream vertexstream;
	std::stringstream fragmentstream;

	vertexfile.open(vertexpath);
	fragmentfile.open(fragmentpath);
	vertexfile.exceptions(std::ifstream::badbit);
	fragmentfile.exceptions(std::ifstream::badbit);
	try {
		if (!vertexfile.is_open() || !fragmentfile.is_open())
		{
			throw std::exception("open file error");
		}
		vertexstream << vertexfile.rdbuf();
		fragmentstream << fragmentfile.rdbuf();
		vertexstring = vertexstream.str();
		fragmentstring = fragmentstream.str();

		vertexsource = vertexstring.c_str();
		fragmentsource = fragmentstring.c_str();
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

void ShowImage::DrawInit()
{
// ������Ҫ�ظ����������Σ������޸ĳ�����
}

void ShowImage::DrawStride(float* fx)
{
	glUseProgram(id);
	unsigned int data = glGetUniformLocation(id,"data");
	glUniform3f(data, fx[0], fx[1], fx[2]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glfwSwapBuffers(window);
	glfwPollEvents();

}

void ShowImage::Checkererrors(unsigned int ID, std::string type)
{
	int success;
	char folog[512];

	if (type != "PROGRAM")
	{
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);//
		if (!success)
		{

			glGetShaderInfoLog(ID, 512, NULL, folog);//
			std::cout << "shader error:" << folog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(id, 512, NULL, folog);
			std::cout << "program error:" << folog << std::endl;
		}
	}
}

ShowImage::~ShowImage()
{
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteProgram(id);
	glfwTerminate();
}

