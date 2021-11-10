#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <SOIL2/SOIL2.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"Shader.h"
#include"Camera.h"

const GLint WIDTH = 800, HEIGHT = 600;

// 键盘响应
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
void DoMovement();

bool keys[1024];
Camera camera(glm::vec3(0.0f, 0.0f, 2.0f));
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

GLfloat	lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;

bool firstMouse = true;

int main()
{
	glfwInit();// 初始化GLFW库
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT,
		"Learn OpenGL B19030409", nullptr, nullptr);
	if (nullptr == window)
	{// 判断window是否正确打开
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	glfwMakeContextCurrent(window);

	// glfwSetKeyCallback(window, KeyCallback);
	// glfwSetCursorPosCallback(window, MouseCallback);
	// glfwSetScrollCallback(window, ScrollCallback);

	// glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{// 判断glew是否正确初始化
		std::cout << "Failed to initialise GLEW" << std::endl;
		return -1;
	}
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Shader ourShader = Shader("core_vs3.txt", "core_fs3.txt");

	GLfloat vertices[] =
	{   // position               color
		-0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,

		 0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 1.0f,
	};

	/* the data should transfer to the memony on Graphic Card|数据应传输到显卡上的内存中 */
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	// 生成缓冲区对象名称
	glGenBuffers(1, &VBO);
	/* connect the VAO and VBO|绑定VAO和VBO */
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	/* trnsfer the data|传输数据 */
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
		vertices, GL_STATIC_DRAW);
	/* set the attribute|设置属性 */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
		6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// 解绑
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	Shader ourShader2 = Shader("core_vs3.txt", "core_fs3.txt");
	GLfloat vertices2[] =
	{   // position               color
		-0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 1.0f,

		-0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,

		 0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 1.0f,
	};

	/* the data should transfer to the memony on Graphic Card|数据应传输到显卡上的内存中 */
	glGenVertexArrays(1, &VAO);
	// 生成缓冲区对象名称
	glGenBuffers(1, &VBO);
	/* connect the VAO and VBO|绑定VAO和VBO */
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	/* trnsfer the data|传输数据 */
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2),
		vertices2, GL_STATIC_DRAW);
	/* set the attribute|设置属性 */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
		6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// 解绑
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



	/* draw loop|绘图循环 */
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currenTime = glfwGetTime();
		deltaTime = currenTime - lastTime;
		lastTime = currenTime;

		glViewport(0, 0, screenWidth, screenHeight);
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glm::mat4 transform1 = glm::mat4(1.0f);
		glm::mat4 transform2 = glm::mat4(1.0f);
		// transform = glm::rotate(transform, glm::radians(20.0f) * static_cast<GLfloat>(glfwGetTime()), glm::vec3(1.0f, 1.0f, 1.0f)); // 旋转
		// transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f)); // 缩放
		// transform = glm::translate(transform, glm::vec3(0.4f, 0.0f, 0.0f)); // 平移
		//平移
		transform1 = glm::translate(transform1, glm::vec3(-cos(currenTime) / 1.2, -sin(currenTime) / 4, -sin(currenTime) / 1.2));
		//旋转
		transform1 = glm::rotate(transform1, glm::radians(20.0f) * static_cast<GLfloat>(glfwGetTime() * 2),
			glm::vec3(-1.0f, -1.0f, -1.0f));
		//缩放
		transform1 = glm::scale(transform1, glm::vec3(0.2f, 0.2f, 0.2f));



		ourShader.Use();
		glUniformMatrix4fv(glGetUniformLocation(ourShader.shaderProgram, "transform"),
			1, GL_FALSE, glm::value_ptr(transform1));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		transform2 = glm::rotate(transform2, glm::radians(20.0f) * static_cast<GLfloat>(glfwGetTime()),
			glm::vec3(-1.0f, -1.0f, -1.0f));
		transform2 = glm::scale(transform2, glm::vec3(0.4f, 0.4f, 0.4f));


		ourShader2.Use();
		glUniformMatrix4fv(glGetUniformLocation(ourShader2.shaderProgram, "transform"),
			1, GL_FALSE, glm::value_ptr(transform2));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();

	return 0;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			keys[key] = false;
		}
	}
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos) {
	if (firstMouse) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	// Process the camera direction
	camera.ProcessMouseMovement(xOffset, yOffset);

}
void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{

}

void DoMovement() {
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) {
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) {
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) {
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) {
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
}

