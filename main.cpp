#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <iostream>
#include "main.h"
#include"Shader.h"


const unsigned int width = 1600; //Window Width
const unsigned int height = 900; //Window Height


int main()
{
//GLFW
	glfwInit(); //Initialize the GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Define the major version of OpenGL - [3].3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Define the minor version of OpenGL - 3.[3]
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Define the OpenGL Profile - Core
	

//WINDOW INTITALIZATION
	GLFWwindow* window = glfwCreateWindow(width, height, "OPENGL DEMO", NULL, NULL); //Create window
	if (window == NULL) //NULL check
	{
		std::cout << "Failed to load window" << "\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); //Make the window current context of the thread

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) //GLAD Initialization for OPENGL functions, NULL Check
	{
		std::cout << "Failed to initialize GLAD" << "\n";
		return -1;
	}

	glViewport(0, 0, width, height); //Set the window coords for OPENGL

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //Make a callback to buffer every time window is resized
	

//VERTEX DATA
	//triangle
	float vertices[] = {
		//pos //clr
		0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f
	};

//SHADER
	Shader shader("vertexshader.vs", "fragmentshader.fs");

//GL PROCESSING
	unsigned int VBO, VAO; //Vertex Buffer Object , Vertex Attribute Object , Element Buffer Object

	glGenVertexArrays(1, &VAO); //Generate Vertex Attribute Arrays
	glGenBuffers(1, &VBO); //Generate a buffer at VBO's address

	glBindVertexArray(VAO);//bind the vertex attribute objects before binding buffers
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //Bind VBO to OPENGL's ARRAY buffer 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Copies the vertex data to the buffer's memory
	
	//glvertexAttribPointer(Pos of attrib to config, Size of attrib, Type of attrib, Normalization, Space b/w attribs, Offset);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //tell OPENGL how to interpret the vertex data
	glEnableVertexAttribArray(0); //Enable the vertex attribute

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


//RENDER LOOP
	while (!glfwWindowShouldClose(window)) //Check for close window call
	{
		//Input
		ProcessInput(window);

		//Rendering
		glClearColor(0.5f, 0.6f, 0.7f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		//Drawing
		shader.use();
		shader.setFloat("offset", 0.0f);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Wireframe Mode

		//Events and Buffers
		glfwSwapBuffers(window); //swaps the front and back buffers
		glfwPollEvents(); //Registers events and calls respective functions
	}


//END
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate(); //Clean up GLFW from memory after closing window
	return 0;
}