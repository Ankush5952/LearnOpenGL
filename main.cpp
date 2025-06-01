#include "main.h"

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
#pragma region WINDOW_INIT
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

	stbi_set_flip_vertically_on_load(true);

	glEnable(GL_DEPTH_TEST); //prevent z-buffer by enabling depth test
	glDepthFunc(GL_LESS);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //trapping cursor within window bounds and making it invisible
#pragma endregion

//MODEL DATA
#pragma region MODEL DATA
	Model bag(FileSystem::getPath("resources/objects/bag/backpack.obj"));
#pragma endregion

//DEMO ITEM
#pragma region DEMO_MESH
	std::vector<Vertex> vertices = {
		Vertex(glm::vec3(-0.3f,-0.3f,0.0f), glm::vec3(0.0f,0.0f,1.0f), glm::vec2(0.0f,0.0f)),
		Vertex(glm::vec3(0.3f,-0.3f,0.0f), glm::vec3(0.0f,0.0f,1.0f), glm::vec2(0.0f,0.0f)),
		Vertex(glm::vec3(0.0f,0.3f,0.0f), glm::vec3(0.0f,0.0f,1.0f), glm::vec2(0.0f,0.0f)),
	};
	std::vector<unsigned int> indices = { 0,1,2 };
	std::vector<Texture> textures;

	Mesh m = Mesh(vertices, indices, textures);
#pragma endregion

//SHADERS
#pragma region SHADER INIT
	Shader shader("shaders/vertexshader.vert", "shaders/fragmentshader.frag");
	Shader border("shaders/vertexshader.vert", "shaders/border.frag");
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
		glClearColor(0.2f, 0.2f, 0.2f, 1); //bg clr
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//Drawing : BIND->TRANSFORM->DRAW
		view = cam.getViewMatrix();

		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
		shader.use();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		shader.setMat4("model", model);
		shader.setMat4("view", view);
		shader.setMat4("proj", proj);

		bag.Draw(shader);

		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glDisable(GL_DEPTH_TEST);
		border.use();
		model = glm::mat4(1.0f);
		model = glm::scale(model,glm::vec3(1.01f));
		border.setMat4("model", model);
		border.setMat4("view", view);
		border.setMat4("proj", proj);
		bag.Draw(border);
		glStencilMask(0xFF);
		glStencilFunc(GL_ALWAYS, 0, 0xFF);
		glEnable(GL_DEPTH_TEST);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Wireframe Mode

		//Events and Buffers
		glfwSwapBuffers(window); //swaps the front and back buffers
		glfwPollEvents(); //Registers events and calls respective functions
	}


//END
#pragma region CLEAR MEMORY
	glfwTerminate(); //Clean up GLFW from memory after closing window
#pragma endregion
	return 0;
}