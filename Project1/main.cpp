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
	GLfloat cube[40];
	CreateCube(0.5f, cube);
	GLint ibo[36];
	CreateEBO(ibo);
	cubeVBO = new VertexBufferObject(cube,40);
	cubeIBO = new ElementBufferObject(ibo,36);
	cubeVAO = new VertexArrayObject(2);
	cubeVAO->Bind();
	cubeVBO->BufferData(GL_STATIC_DRAW);
	cubeIBO->BufferData(GL_STATIC_DRAW);
	cubeVAO->SetVBO(cubeVBO);
	cubeVAO->SetIBO(cubeIBO);
	cubePosition = new Attribute("position", 0, 3, 5 * sizeof(GLfloat), 0, GL_FLOAT, GL_FALSE);
	cubeVAO->AddAttribute(0, *cubePosition);
	cubeTexcoords = new Attribute("texcoords", 1, 2, 5 * sizeof(GLfloat), 3 * sizeof(GLfloat), GL_FLOAT, GL_FALSE);
	cubeVAO->AddAttribute(1, *cubeTexcoords);
	cubeVAO->SetAttributes();
	cubeVAO->Unbind();
	//create skybox buffers
	GLfloat skybox[108];
	CreateSkyBoxCube(10.0f, skybox);
	skyboxVBO = new VertexBufferObject(skybox,108);
	skyboxVAO = new VertexArrayObject(1);
	skyboxVAO->Bind();
	skyboxVBO->BufferData(GL_STATIC_DRAW);
	skyboxVAO->SetVBO(skyboxVBO);
	skyboxPosition = new Attribute("position", 0, 3, 3 * sizeof(GLfloat), 0, GL_FLOAT, GL_FALSE);
	skyboxVAO->AddAttribute(0, *skyboxPosition);
	skyboxVAO->SetAttributes();
	skyboxVAO->Unbind();
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
	cubeTexture->Activate(GL_TEXTURE0);
	cubeTexture->Bind();
	glUniform1i(uniform_cubetexture, 0);
	glUniformMatrix4fv(uniform_cubeModel, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(uniform_cubeView, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(uniform_cubeProjection, 1, GL_FALSE, glm::value_ptr(projection));
	cubeVAO->Bind();
	cubeVAO->Draw();
	cubeVAO->Unbind();
	cubeTexture->Unbind();
	//draw sky box
	glDepthFunc(GL_LEQUAL);
	skyboxshader->Use();
	skyboxTexture->Activate(GL_TEXTURE1);
	skyboxTexture->Bind();
	glUniform1i(uniform_skyboxtexture, 1);
	glUniformMatrix4fv(uniform_skyboxView, 1, GL_FALSE, glm::value_ptr(skyboxview));
	glUniformMatrix4fv(uniform_skyboxProjection, 1, GL_FALSE, glm::value_ptr(projection));
	skyboxVAO->Bind();
	skyboxVAO->Draw(0, 36);
	skyboxVAO->Unbind();
	skyboxTexture->Unbind();
}
