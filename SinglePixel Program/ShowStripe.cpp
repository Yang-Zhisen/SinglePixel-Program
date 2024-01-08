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
	//进行Opengl初始化
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//任何OpenGL的展示均需要窗口，因此窗口创建直接在初始化中进行
	getMonitors= glfwGetMonitors(&Monitor);
	window = glfwCreateWindow(wide, height, "test window", getMonitors[0], NULL);

	if (window == NULL)
	{
		std::cout << "打开错误" << std::endl;
		glfwTerminate();//终止
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
	//对 vao,vbo,ebo 做初建立
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//在这耽误一天，顶点数据需要被解析-----------------------------------
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}


void ShowImage::ShaderInit()
{
	//对着色器进行初始化创建
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexsource, NULL);
	glCompileShader(vertex);
	Checkererrors(vertex, "Vertex");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentsource, NULL);
	glCompileShader(fragment);
	Checkererrors(fragment, "Fragment");


	//因一直使用，就将着色器在此链接并激活
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
// 当下需要重复绘制三角形，后续修改成纹理
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

