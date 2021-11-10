#pragma once

#ifndef Light_h
#define Light_h
#endif // !Light_h

#include<GL/glew.h>
#include"Shader.h"



GLfloat vertices[] =
{
	//position              
	-0.5f,-0.5f,-0.5f,
	0.5f,-0.5f,-0.5f,
	0.5f,0.5f,-0.5f,
	0.5f,0.5f,-0.5f,
	-0.5f,0.5f,-0.5f,
	-0.5f,-0.5f,-0.5f,

	-0.5f,-0.5f,0.5f,
	0.5f,-0.5f,0.5f,
	0.5f,0.5f,0.5f,
	0.5f,0.5f,0.5f,
	-0.5f,0.5f,0.5f,
	-0.5f,-0.5f,0.5f,

	-0.5f,0.5f,0.5f,
	-0.5f,0.5f,-0.5f,
	-0.5f,-0.5f,-0.5f,
	-0.5f,-0.5f,-0.5f,
	-0.5f,-0.5f,0.5f,
	-0.5f,0.5f,0.5f,

	0.5f,0.5f,0.5f,
	0.5f,0.5f,-0.5f,
	0.5f,-0.5f,-0.5f,
	0.5f,-0.5f,-0.5f,
	0.5f,-0.5f,0.5f,
   0.5f,0.5f,0.5f,

   -0.5f,-0.5f,-0.5f,
   0.5f,-0.5f,-0.5f,
   0.5f,-0.5f,0.5f,
   0.5f,-0.5f,0.5f,
   -0.5f,-0.5f,0.5f,
   -0.5f,-0.5f,-0.5f,

   -0.5f,0.5f,-0.5f,
   0.5f,0.5f,-0.5f,
   0.5f,0.5f,0.5f,
   0.5f,0.5f,0.5f,
   -0.5f,0.5f,0.5f,
   -0.5f,0.5f,-0.5f,
};

class Light
{
public:
	Light()
	{
		this->update();
	}
	void Draw(Shader& shader)
	{
		glBindVertexArray(this->VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}

private:
	GLuint VAO, VBO;
	void update()
	{
		glGenVertexArrays(1, &this->VAO);//顶点阵列着色器，先绑定VAO
		glGenBuffers(1, &this->VBO);//顶点缓存着色器
		//conect the VAO and VBO
		glBindVertexArray(this->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);//顶点基本信息
		//transfer the data将buffer数据传输
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		//set the attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);//3个浮点数，对应position0的位置，后三个参数对应VBO
		glEnableVertexAttribArray(0);//开启第零个通道
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}
};


