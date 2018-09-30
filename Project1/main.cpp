#include "main.h"
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Skybox and Box in c++", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialise GLEW" << std::endl;
		return -1;
	}
	glfwSetKeyCallback(window, Key_Callback);
	glfwSetErrorCallback(Error_Callback);
	glViewport(0, 0, 800, 600);
	initProgram();
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		UpdateFrame();
		RenderFrame();
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}

void Key_Callback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
}
void Error_Callback(int n, const char * error)
{
	std::cout << "An error occured: " << error << std::endl;
}
void initProgram()
{
	//cube shader
	cubeshader = new Shader("C:\\Users\\me\\Documents\\Visual Studio 2015\\Projects\\Project1\\Debug\\cube.vert",
		"C:\\Users\\me\\Documents\\Visual Studio 2015\\Projects\\Project1\\Debug\\cube.frag");
	//skybox shader
	skyboxshader = new Shader("C:\\Users\\me\\Documents\\Visual Studio 2015\\Projects\\Project1\\Debug\\skybox.vert",
		"C:\\Users\\me\\Documents\\Visual Studio 2015\\Projects\\Project1\\Debug\\skybox.frag");
	//get attributes and uniforms
	attribute_cube = cubeshader->GetAttributeHandle("position");
	attribute_cube_texcoords = cubeshader->GetAttributeHandle("texcoords");
	attribute_skybox = skyboxshader->GetAttributeHandle("position");
	uniform_cubeModel = cubeshader->GetUniformHandle("model");
	uniform_cubeView = cubeshader->GetUniformHandle("view");
	uniform_cubeProjection = cubeshader->GetUniformHandle("projection");
	uniform_cubetexture = cubeshader->GetUniformHandle("cubetexture");
	uniform_skyboxView = skyboxshader->GetUniformHandle("view");
	uniform_skyboxProjection = skyboxshader->GetUniformHandle("projection");
	uniform_skyboxtexture = skyboxshader->GetUniformHandle("skybox");
	if (attribute_cube == -1 || attribute_cube_texcoords == -1 || attribute_skybox == -1 || uniform_cubeModel == -1 || uniform_cubeProjection == -1 ||
		uniform_cubetexture == -1 || uniform_cubeView == -1 || uniform_skyboxProjection == -1 || uniform_skyboxtexture == -1 || uniform_skyboxView == -1)
	{
		std::cout << "Error finding uniforms and attributes" << std::endl;
	}
	//create cube buffers
	glGenBuffers(1, &cubeVBO);
	glGenBuffers(1, &cubeIBO);
	glGenVertexArrays(1, &cubeVAO);
	glBindVertexArray(cubeVAO);
	GLfloat cube[40]; 
	CreateCube(0.5f,cube);
	GLint ibo[36];
	CreateEBO(ibo);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), &cube, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ibo), &ibo, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	//create skybox buffers
	glGenBuffers(1, &skyboxVBO);
	glGenVertexArrays(1, &skyboxVAO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	GLfloat skybox[108];
	CreateSkyBoxCube(10.0f,skybox);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skybox), &skybox, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	//cube texture
	cubeTexture = new Texture("C:\\Users\\me\\Documents\\Visual Studio 2015\\Projects\\Project1\\Debug\\Container2.png");
	cubeTexture->SetTexParameterI(GL_TEXTURE_WRAP_S, GL_REPEAT);
	cubeTexture->SetTexParameterI(GL_TEXTURE_WRAP_T, GL_REPEAT);
	cubeTexture->SetTexParameterI(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	cubeTexture->SetTexParameterI(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//skybox texture
	skyboxTexture = new Texture("C:\\Users\\me\\Documents\\Visual Studio 2015\\Projects\\Project1\\Debug\\top.png",
		"C:\\Users\\me\\Documents\\Visual Studio 2015\\Projects\\Project1\\Debug\\bottom.png",
		"C:\\Users\\me\\Documents\\Visual Studio 2015\\Projects\\Project1\\Debug\\left.png",
		"C:\\Users\\me\\Documents\\Visual Studio 2015\\Projects\\Project1\\Debug\\right.png",
		"C:\\Users\\me\\Documents\\Visual Studio 2015\\Projects\\Project1\\Debug\\front.png",
		"C:\\Users\\me\\Documents\\Visual Studio 2015\\Projects\\Project1\\Debug\\back.png");
	skyboxTexture->SetTexParameterI(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	skyboxTexture->SetTexParameterI(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	skyboxTexture->SetTexParameterI(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	skyboxTexture->SetTexParameterI(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	skyboxTexture->SetTexParameterI(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glClearColor(0.5f, 0.1f, 0.5f, 1.0f);
	camerapos = glm::vec3(-7.0f, 7.0f, -7.0f);
	lookatpos = glm::vec3(0.0f, 0.0f, 0.0f);
	model = glm::mat4(1.0f);
	skyboxview = glm::mat4(1.0f);
	view = glm::mat4(1.0f);

}

void LoadTexture(const GLchar * filename, GLuint * textureindex)
{
	glGenTextures(1, textureindex);
	glBindTexture(GL_TEXTURE_2D, *textureindex);
	int width, height;
	unsigned char* texture = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void LoadSkyBoxTexture(const std::string* filenames, GLuint * SkyboxIndex)
{
	glGenTextures(1, SkyboxIndex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, *SkyboxIndex);
	int width, height;
	unsigned char* texture;
	for (int n = 0; n < 6; n++)
	{
		texture = SOIL_load_image(filenames[n].c_str(), &width, &height,0, SOIL_LOAD_RGB);
		switch (n)
		{
			case 0:
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
				break;
			case 1:
				glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
				break;
			case 2:
				glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
				break;
			case 3:
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
				break;
			case 4:
				glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
				break;
			case 5:
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
				break;	
		}
		SOIL_free_image_data(texture);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CreateCube(float size, GLfloat* cube)
{
	GLfloat thecube[] =
	{
		-size,size,-size,1.0,0.0,
		-size,size,size,1.0,1.0,
		-size,-size,-size,0.0,0.0,
		-size,-size,size,0.0,1.0,
		size,size,-size,1.0,0.0,
		size,size,size,1.0,1.0,
		size,-size,-size,0.0,0.0,
		size,-size,size,0.0,1.0 
	};
	for (int n = 0; n < 40; n++)
	{
		cube[n] = thecube[n];
	}
}
	

void CreateEBO(GLint* cube)
{
	GLint thecube[] =
	{
		//left
		0,1,3,
		3,2,0,
		//right
		4,6,7,
		6,5,4,
		//top
		5,1,0,
		0,4,5,
		//bottom
		7,3,2,
		2,6,7,
		//front
		0,2,6,
		6,4,0,
		//back
		5,1,3,
		3,7,5
	};
	for (int n = 0; n < 36; n++)
	{
		cube[n] = thecube[n];
	}
	
}

void CreateSkyBoxCube(float size, GLfloat* skybox)
{
	GLfloat theskybox[] =
	{
		-size,  size, -size,
		-size, -size, -size,
		size, -size, -size,
		size, -size, -size,
		size,  size, -size,
		-size,  size, -size,

		-size, -size,  size,
		-size, -size, -size,
		-size,  size, -size,
		-size,  size, -size,
		-size,  size,  size,
		-size, -size,  size,

		size, -size, -size,
		size, -size,  size,
		size,  size,  size,
		size,  size,  size,
		size,  size, -size,
		size, -size, -size,

		-size, -size,  size,
		-size,  size,  size,
		size,  size,  size,
		size,  size,  size,
		size, -size,  size,
		-size, -size,  size,

		-size,  size, -size,
		size,  size, -size,
		size,  size,  size,
		size,  size,  size,
		-size,  size,  size,
		-size,  size, -size,

		-size, -size, -size,
		-size, -size,  size,
		size, -size, -size,
		size, -size, -size,
		-size, -size,  size,
		size, -size, size
	};
	for (int n = 0; n < 108; n++)
	{
		skybox[n] = theskybox[n];
	}
}

void UpdateFrame()
{
	model = glm::rotate(model, -55.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::lookAt(camerapos, lookatpos, glm::vec3(0.0, 1.0, 0.0));
	projection = glm::perspective(90.0f, (float)(800 / 600), 0.1f, 100.0f);
	skyboxview = glm::lookAt(camerapos, lookatpos, glm::vec3(0.0f, 1.0f, 0.0f));
}

void RenderFrame()
{
	//clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//draw cube
	glDepthFunc(GL_LESS);
	cubeshader->Use();
	glActiveTexture(GL_TEXTURE0);
	cubeTexture->Bind();
	glUniform1i(uniform_cubetexture, 0);
	glUniformMatrix4fv(uniform_cubeModel, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(uniform_cubeView, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(uniform_cubeProjection, 1, GL_FALSE, glm::value_ptr(projection));
	glBindVertexArray(cubeVAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	cubeTexture->Unbind();
	//draw sky box
	glDepthFunc(GL_LEQUAL);
	skyboxshader->Use();
	glActiveTexture(GL_TEXTURE1);
	skyboxTexture->Bind();
	glUniform1i(uniform_skyboxtexture, 1);
	glUniformMatrix4fv(uniform_skyboxView, 1, GL_FALSE, glm::value_ptr(skyboxview));
	glUniformMatrix4fv(uniform_skyboxProjection, 1, GL_FALSE, glm::value_ptr(projection));
	glBindVertexArray(skyboxVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	skyboxTexture->Unbind();
}
