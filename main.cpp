#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <iostream>
#include<stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include "main.h"
#include"Shader.h"

//STATIC VARIABLES
#pragma region STATIC VARIABLES
const unsigned int width = 1600; //Window Width
const unsigned int height = 900; //Window Height
#pragma endregion


int main()
{
//GLFW
#pragma region GLFW
	glfwInit(); //Initialize the GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Define the major version of OpenGL - [3].3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Define the minor version of OpenGL - 3.[3]
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Define the OpenGL Profile - Core
#pragma endregion
	
//WINDOW INTITALIZATION
#pragma region MyRegion
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
#pragma endregion

//VERTEX DATA
#pragma region VERTEX DATA
	//vertex coords = (x,y,z) ; similar to coordinate axis
	float vertices[] = {
		//pos //tex
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, //bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, //bottom left
		0.0f, 0.5f, 0.0f, 0.5f, 1.0f // top
	};

	//cube
	float v2[] = {
		-0.3f, -0.3f, -0.3f, 0.0f, 0.0f,
		0.3f, -0.3f, -0.3f, 1.0f, 0.0f,
		0.3f, 0.3f, -0.3f, 1.0f, 1.0f,

		0.3f, 0.3f, -0.3f, 1.0f, 1.0f,
		-0.3f, 0.3f, -0.3f, 0.0f, 1.0f,
		-0.3f, -0.3f, -0.3f, 0.0f, 0.0f,

		-0.3f, -0.3f, 0.3f, 0.0f, 0.0f,
		0.3f, -0.3f, 0.3f, 1.0f, 0.0f,
		0.3f, 0.3f, 0.3f, 1.0f, 1.0f,

		0.3f, 0.3f, 0.3f, 1.0f, 1.0f,
		-0.3f, 0.3f, 0.3f, 0.0f, 1.0f,
		-0.3f, -0.3f, 0.3f, 0.0f, 0.0f,

		-0.3f, 0.3f, 0.3f, 1.0f, 0.0f,
		-0.3f, 0.3f, -0.3f, 1.0f, 1.0f,
		-0.3f, -0.3f, -0.3f, 0.0f, 1.0f,

		-0.3f, -0.3f, -0.3f, 0.0f, 1.0f,
		-0.3f, -0.3f, 0.3f, 0.0f, 0.0f,
		-0.3f, 0.3f, 0.3f, 1.0f, 0.0f,

		0.3f, 0.3f, 0.3f, 1.0f, 0.0f,
		0.3f, 0.3f, -0.3f, 1.0f, 1.0f,
		0.3f, -0.3f, -0.3f, 0.0f, 1.0f,

		0.3f, -0.3f, -0.3f, 0.0f, 1.0f,
		0.3f, -0.3f, 0.3f, 0.0f, 0.0f,
		0.3f, 0.3f, 0.3f, 1.0f, 0.0f,

		-0.3f, -0.3f, -0.3f, 0.0f, 1.0f,
		0.3f, -0.3f, -0.3f, 1.0f, 1.0f,
		0.3f, -0.3f, 0.3f, 1.0f, 0.0f,

		0.3f, -0.3f, 0.3f, 1.0f, 0.0f,
		-0.3f, -0.3f, 0.3f, 0.0f, 0.0f,
		-0.3f, -0.3f, -0.3f, 0.0f, 1.0f,

		-0.3f, 0.3f, -0.3f, 0.0f, 1.0f,
		0.3f, 0.3f, -0.3f, 1.0f, 1.0f,
		0.3f, 0.3f, 0.3f, 1.0f, 0.0f,

		0.3f, 0.3f, 0.3f, 1.0f, 0.0f,
		-0.3f, 0.3f, 0.3f, 0.0f, 0.0f,
		-0.3f, 0.3f, -0.3f, 0.0f, 1.0f
	};
#pragma endregion

//SHADER
#pragma region SHADER INIT
	Shader shader("vertexshader.vs", "fragmentshader.fs");
#pragma endregion

//VERTEX PROCESSING
#pragma region VERTEX PROCESSING
	unsigned int VBO, VAO; //Vertex Buffer Object , Vertex Attribute Object , Element Buffer Object

	glGenVertexArrays(1, &VAO); //Generate Vertex Attribute Arrays
	glGenBuffers(1, &VBO); //Generate a buffer at VBO's address

	glBindVertexArray(VAO);//bind the vertex attribute objects before binding buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //Bind VBO to OPENGL's ARRAY buffer 
	glBufferData(GL_ARRAY_BUFFER, sizeof(v2), v2, GL_STATIC_DRAW); //Copies the vertex data to the buffer's memory

	//glvertexAttribPointer(Pos of attrib to config, Size of attrib, Type of attrib, Normalization, Space b/w attribs, Offset);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); //position coordinates
	glEnableVertexAttribArray(0); //Enable the vertex attribute

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); //texture coordinates
	glEnableVertexAttribArray(1);
#pragma endregion

//TEXTURE PROCESSING
#pragma region TEXTURE PROCESSING
	//texture coords = (s,t,r) ; for 2D tex = (s,t); s> ,t^
	unsigned int texture1, texture2;
	//tex-1
	glGenTextures(1, &texture1); //generate a texture
	glBindTexture(GL_TEXTURE_2D, texture1); //bind the texture

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //defining the 2D texture properties for s coordinate
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //defining the 2D texture properties for t coordinate
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //defining the minimization filter method using mipmap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //defining the magnification filter method

	int twidth, theight, nchannels;

	unsigned char* tdata = stbi_load("wood.jpg", &twidth, &theight, &nchannels,0); //load the texture image
	//check for error
	if(tdata)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata); //generate texture from image
		glGenerateMipmap(GL_TEXTURE_2D); //generate mipmap
	}
	else
	{
		std::cout << "FAILED TO LOAD TEXTURE IMAGE 1\n";
	}

	stbi_image_free(tdata); //free the image data after processing
	//tex-2
	glGenTextures(1, &texture2); //generate a texture
	glBindTexture(GL_TEXTURE_2D, texture2); //bind the texture

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //defining the 2D texture properties for s coordinate
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //defining the 2D texture properties for t coordinate
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //defining the minimization filter method using mipmap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //defining the magnification filter method

	stbi_set_flip_vertically_on_load(true);
	tdata = stbi_load("smily.png", &twidth, &theight, &nchannels, 0); //load the texture image
	//check for error
	if(tdata)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, twidth, theight, 0, GL_RGBA, GL_UNSIGNED_BYTE, tdata); //generate texture from image
		glGenerateMipmap(GL_TEXTURE_2D); //generate mipmap
	}
	else
	{
		std::cout << "FAILED TO LOAD TEXTURE IMAGE 2\n";
	}

	stbi_image_free(tdata); //free the image data after processing

	shader.use();
	shader.setInt("Texture1", 0);
	shader.setInt("Texture2", 1);
#pragma endregion

//TRANSFORMATION
#pragma region STATIC TRANSFORM
	glm::mat4 trans = glm::mat4(1.0f);
	unsigned int transformID = glGetUniformLocation(shader.ID, "transform");
#pragma endregion

//COORDINATE TRANSFORMATION MATRICES
#pragma region COORDINATE TRANSFORMATION MATRICES
	//model matrix
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model,glm::radians(-80.0f),glm::vec3(1.0f,0.0f,0.0f));
	//view matrix
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	//projection matrix
	glm::mat4 proj;
	proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f); //perspective projection for realistic 3D
#pragma endregion

	glEnable(GL_DEPTH_TEST);
//RENDER LOOP
	while (!glfwWindowShouldClose(window)) //Check for close window call
	{
		//Input
		ProcessInput(window);

		//Rendering
		glClearColor(0.3f, 0.3f, 0.3f, 1); //bg clr
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Drawing
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		shader.use();
		shader.setFloat("offset", 0.0f);

		//BIND -> TRANSFORM -> DRAW
		glBindVertexArray(VAO);

		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians((float)glfwGetTime()*3), glm::vec3(1.0f, 1.0f, 0.0f));

		shader.setMat4("model", model);
		shader.setMat4("view", view);
		shader.setMat4("proj", proj);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Wireframe Mode

		//Events and Buffers
		glfwSwapBuffers(window); //swaps the front and back buffers
		glfwPollEvents(); //Registers events and calls respective functions
	}


//END
#pragma region CLEAR MEMORY
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate(); //Clean up GLFW from memory after closing window
#pragma endregion
	return 0;
}