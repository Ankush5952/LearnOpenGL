#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <iostream>
#include "main.h"


const unsigned int width = 1600; //Window Width
const unsigned int height = 900; //Window Height

//BASIC SHADER SOURCE
	//GLSL vertex shader
const char* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos, 1.0);\n"
	"}\0";

	//GLSL fragment shader
	const char* fragmentShaderSource = "#version 330 core\n"
		"uniform vec4 vertexclr;\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vertexclr;\n"
		"}\n\0";


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
		-0.9f, 0.9f, 0.0f,
		-0.9f, 0.8f, 0.0f,
		-0.8f, 0.8f, 0.0f
	};

	//rectangle
	float vertices2[] = {
		//tri 1
		0.5f, 0.5f, 0.0f, //top right
		0.5f, -0.5f, 0.0f, //bottom right
		-0.5f, -0.5f, 0.0f, //bottom left
		-0.5f, 0.5f, 0.0f, //top left
	};

	unsigned int indices[] = {
		0, 1, 3, //tri 1
		1, 2, 3 //tri 2
	};

	//2 triangles
	float vertices3[] = {
			-0.9f, 0.9f, 0.0f,
			-0.9f, 0.8f, 0.0f,
			-0.8f, 0.8f, 0.0f,
			-0.7f,0.9f,0.0f,
			-0.7f,0.8f,0.0f,
			-0.8f,0.8f,0.0f
		};

//GL PROCESSING
	unsigned int VBO, VAO, EBO; //Vertex Buffer Object , Vertex Attribute Object , Element Buffer Object

	glGenBuffers(1, &EBO); //Generate a buffer at EBO's address
	glGenVertexArrays(1, &VAO); //Generate Vertex Attribute Arrays
	glGenBuffers(1, &VBO); //Generate a buffer at VBO's address

	glBindVertexArray(VAO);//bind the vertex attribute objects before binding buffers
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //Bind VBO to OPENGL's ARRAY buffer 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW); //Copies the vertex data to the buffer's memory
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //Bind EBO to Element Array Buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); //copy the indice data to buffer memory

	//glvertexAttribPointer(Pos of attrib to config, Size of attrib, Type of attrib, Normalization, Space b/w attribs, Offset);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //tell OPENGL how to interpret the vertex data
	glEnableVertexAttribArray(0); //Enable the vertex attribute


//VERTEX SHADER
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER); //Create a vertex shader object for OPENGL
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //link the source code to shader object
	glCompileShader(vertexShader); //compiles the shader object

	//Check shader compilation success
	int success;
	char infolog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
		std::cout << "FAILED TO LOAD VERTEX SHADER" << "\n" << infolog << "\n";
	}

//FRAGMENT SHADER
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //Create a fragment shader object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); //Link source code to shader obj
	glCompileShader(fragmentShader); //Compile the shader obj

	//Check for compilation success
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
		std::cout << "FAILED TO LOAD FRAGMENT SHADER\n" << infolog << "\n";
	}


//SHADER PROGRAM
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram(); //creates a program and returns its ID referance
	glAttachShader(shaderProgram, vertexShader); //Attach vrtex shader to program
	glAttachShader(shaderProgram, fragmentShader); //Attach fragment shader to program
	glLinkProgram(shaderProgram); //Link all shaders together to use them

	//Check for Linking success
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
		std::cout << "FAILED TO LINK SHADER PROGRAM\n" << infolog << "\n";
	}

	//Delete the source shaders coz no longer needed
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


//RENDER LOOP
	while (!glfwWindowShouldClose(window)) //Check for close window call
	{
		//Input
		ProcessInput(window);

		//Rendering
		glClearColor(0.5f, 0.6f, 0.7f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		//Drawing
		glUseProgram(shaderProgram);
		float t = glfwGetTime();
		//std::cout << t << "\n";
		float t01 = (sin(t)+1)/2;
		//std::cout << t01 << "\n";
		int vertexClrIndex = glGetUniformLocation(shaderProgram, "vertexclr");
		glUniform4f(vertexClrIndex, abs(2 * t01 - 1), t01, abs(1 - t01), 1.0f);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Wireframe Mode

		//Events and Buffers
		glfwSwapBuffers(window); //swaps the front and back buffers
		glfwPollEvents(); //Registers events and calls respective functions
	}


//END
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate(); //Clean up GLFW from memory after closing window
	return 0;
}