#include "main.h"
#include"Shader.h"


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
#pragma endregion

//WINDOW SETTINGS
#pragma region WINDOW SETTINGS
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //Make a callback to buffer every time window is resized
	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glEnable(GL_DEPTH_TEST); //prevent z-buffer by enabling depth test

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //trapping cursor within window bounds and making it invisible
#pragma endregion

//VERTEX DATA
#pragma region VERTEX DATA
	//vertex coords = (x,y,z) ; similar to coordinate axis
	// texcoord = (s,t);
	// normal = (x,y,z);
	//cube
	float v2[] = {
		//pos                //tex       //normals
		-0.3f, -0.3f, -0.3f, 0.0f, 0.0f, 0.0f,0.0f,-1.0f,
		0.3f, -0.3f, -0.3f, 1.0f, 0.0f, 0.0f,0.0f,-1.0f,
		0.3f, 0.3f, -0.3f, 1.0f, 1.0f, 0.0f,0.0f,-1.0f,

		0.3f, 0.3f, -0.3f, 1.0f, 1.0f, 0.0f,0.0f,-1.0f,
		-0.3f, 0.3f, -0.3f, 0.0f, 1.0f, 0.0f,0.0f,-1.0f,
		-0.3f, -0.3f, -0.3f, 0.0f, 0.0f, 0.0f,0.0f,-1.0f,

		-0.3f, -0.3f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.3f, -0.3f, 0.3f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.3f, 0.3f, 0.3f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

		0.3f, 0.3f, 0.3f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.3f, 0.3f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.3f, -0.3f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

		-0.3f, 0.3f, 0.3f, 1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
		-0.3f, 0.3f, -0.3f, 1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
		-0.3f, -0.3f, -0.3f, 0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,

		-0.3f, -0.3f, -0.3f, 0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
		-0.3f, -0.3f, 0.3f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
		-0.3f, 0.3f, 0.3f, 1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
		
		0.3f, 0.3f, 0.3f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.3f, 0.3f, -0.3f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.3f, -0.3f, -0.3f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		0.3f, -0.3f, -0.3f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.3f, -0.3f, 0.3f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.3f, 0.3f, 0.3f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		-0.3f, -0.3f, -0.3f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		0.3f, -0.3f, -0.3f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		0.3f, -0.3f, 0.3f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,

		0.3f, -0.3f, 0.3f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		-0.3f, -0.3f, 0.3f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		-0.3f, -0.3f, -0.3f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

		-0.3f, 0.3f, -0.3f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.3f, 0.3f, -0.3f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.3f, 0.3f, 0.3f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		0.3f, 0.3f, 0.3f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.3f, 0.3f, 0.3f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.3f, 0.3f, -0.3f ,0.0f, 1.0f, 0.0f, 1.0f, 0.0f
	};

	glm::vec3 cubePos[] = {
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(1.0f,1.0f,-2.0f),
		glm::vec3(-1.0f,1.0f,-2.0f),
		glm::vec3(1.5f,-1.5f,-5.0f),
		glm::vec3(-1.5f,-2.0f,-7.0f),
	};
#pragma endregion

//SHADER
#pragma region SHADER INIT
	Shader shader("vertexshader.vs", "fragmentshader.fs");
	Shader lightShader("light.vs", "light.fs");

	lightShader.use();
	lightShader.setVec3("lightClr", lightClr);

	shader.use();
	//light
	shader.setVec3("light.ambient", glm::vec3(0.2f)*lightClr);
	shader.setVec3("light.diffuse", glm::vec3(0.5f)* lightClr);
	shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
	//material
	shader.setInt("mat.diffuse", 0);
	shader.setVec3("mat.specular", 0.5f, 0.5f, 0.5f);
	shader.setFloat("mat.shininess", 32.0f);
	//colors
	shader.setVec3("objClr", glm::vec3(1.0f));
#pragma endregion

//VERTEX PROCESSING
#pragma region VERTEX PROCESSING

	glGenVertexArrays(1, &VAO); //Generate Vertex Attribute Arrays
	glGenBuffers(1, &VBO); //Generate a buffer at VBO's address

	glBindVertexArray(VAO);//bind the vertex attribute objects before binding buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //Bind VBO to OPENGL's ARRAY buffer 
	glBufferData(GL_ARRAY_BUFFER, sizeof(v2), v2, GL_STATIC_DRAW); //Copies the vertex data to the buffer's memory
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //pos
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float))); //tex
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float))); //normal
	glEnableVertexAttribArray(2);


	//light VBO
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v2), v2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //pos
	glEnableVertexAttribArray(0);

#pragma endregion

//TEXTURE PROCESSING
#pragma region TEXTURE PROCESSING
	//texture coords = (s,t,r) ; for 2D tex = (s,t); s> ,t^
	int twidth, theight, nchannels;
	unsigned char* tdata;

	//diffuse map
	glGenTextures(1, &diffuseMap);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //defining the 2D texture properties for s coordinate
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //defining the 2D texture properties for t coordinate
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //defining the minimization filter method using mipmap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //defining the magnification filter method
	tdata = stbi_load("container.png", &twidth, &theight, &nchannels, 0);
	if (tdata)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, twidth, theight, 0, GL_RGBA, GL_UNSIGNED_BYTE, tdata); //generate texture from image
		glGenerateMipmap(GL_TEXTURE_2D); //generate mipmap
	}
	else
	{
		std::cout << "FAILED TO LOAD DIFFUSE MAP\n";
	}
	stbi_image_free(tdata);

	//specular map
	glGenTextures(1, &specularMap);
	glBindTexture(GL_TEXTURE_2D, specularMap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //defining the 2D texture properties for s coordinate
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //defining the 2D texture properties for t coordinate
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //defining the minimization filter method using mipmap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //defining the magnification filter method
	tdata = stbi_load("container_specular.png", &twidth, &theight, &nchannels, 0);
	if (tdata)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, twidth, theight, 0, GL_RGBA, GL_UNSIGNED_BYTE, tdata);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "FAILED TO LOAD SPECULAR MAP" << "\n";
	}

	//emission map
	glGenTextures(1, &emissionMap);
	glBindTexture(GL_TEXTURE_2D, emissionMap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //defining the 2D texture properties for s coordinate
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //defining the 2D texture properties for t coordinate
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //defining the minimization filter method using mipmap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //defining the magnification filter method
	tdata = stbi_load("matrix.jpg", &twidth, &theight, &nchannels, 0);
	if (tdata)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "FAILED TO LOAD SPECULAR MAP" << "\n";
	}
	shader.use();
	shader.setInt("mat.diffuse", 0);
	shader.setInt("mat.specular", 1);
	shader.setInt("mat.emission", 2);
#pragma endregion

//TRANSFORMATION
#pragma region STATIC TRANSFORM
	trans = glm::mat4(1.0f);
	unsigned int transformID = glGetUniformLocation(shader.ID, "transform");
#pragma endregion

//COORDINATE TRANSFORMATION MATRICES
#pragma region COORDINATE TRANSFORMATION MATRICES
	//model matrix
	model = glm::mat4(1.0f);

	//view matrix
	view = glm::mat4(1.0f);

	//projection matrix
	proj = glm::perspective(glm::radians(cam.zoom), (float)width / height, 0.1f, 100.0f); //perspective projection for realistic 3D
#pragma endregion

//CAMERA
#pragma region CAMERA

#pragma endregion

//RENDER LOOP
	while (!glfwWindowShouldClose(window)) //Check for close window call
	{
		//Time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//Input
		ProcessInput(window);

		//Zoom
		proj = glm::perspective(glm::radians(cam.zoom), (float)width / height, 0.1f, 100.0f);

		//Rendering
		glClearColor(0.3f, 0.3f, 0.3f, 1); //bg clr
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, emissionMap);

		//Drawing : BIND->TRANSFORM->DRAW
		view = cam.getViewMatrix();

		//light object
		lightShader.use();
		glBindVertexArray(lightVAO);
		model = glm::mat4(1.0f);
		//lightDir = glm::vec4(sin(glfwGetTime()), sin(glfwGetTime()) * cos(glfwGetTime()), cos(glfwGetTime()), lightDir.w);
		lightDir = glm::vec4(sin(glfwGetTime()), lightDir.y, cos(glfwGetTime()), lightDir.w);
		//lightClr = glm::vec3(sin(glfwGetTime()), sin(glfwGetTime()) * cos(glfwGetTime()), cos(glfwGetTime()));
		model = glm::translate(model, glm::vec3(lightDir));
		model = glm::scale(model, glm::vec3(0.2f));
		lightShader.setMat4("lightModel", model);
		lightShader.setMat4("lightView", view);
		lightShader.setMat4("lightProj", proj);
		lightShader.setVec3("lightClr", lightClr);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//cube
		shader.use();
		glBindVertexArray(VAO);
		for (int i = 0; i < 5; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePos[i]);
			float angle = 20 + i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.0f, -1.0f));
			shader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//model = glm::translate(model, cubePos[0]);
		shader.setVec4("light.dir", lightDir);
		shader.setVec3("light.ambient", glm::vec3(0.2f) * lightClr);
		shader.setVec3("light.diffuse", glm::vec3(0.5f) * lightClr);
		//shader.setMat4("model", model);
		shader.setVec3("viewPos", cam.pos);
		shader.setMat4("view", view);
		shader.setMat4("proj", proj);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Wireframe Mode

		//Events and Buffers
		glfwSwapBuffers(window); //swaps the front and back buffers
		glfwPollEvents(); //Registers events and calls respective functions
	}


//END
#pragma region CLEAR MEMORY
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate(); //Clean up GLFW from memory after closing window
#pragma endregion
	return 0;
}