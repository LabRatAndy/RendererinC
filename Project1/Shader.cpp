#include"Shader.h"


	Shader::Shader(const GLchar* vertexShaderfile, const GLchar* fragmentShaderfile)
	{
		handle = glCreateProgram();
		LoadShader(vertexShaderfile, GL_VERTEX_SHADER);
		LoadShader(fragmentShaderfile, GL_FRAGMENT_SHADER);
		glAttachShader(handle, vertexShader);
		glAttachShader(handle, fragmentShader);
		glLinkProgram(handle);
		int sucess;
		glGetProgramiv(handle, GL_LINK_STATUS, &sucess);
		if (!sucess)
		{
			GLchar error[512];
			glGetProgramInfoLog(handle, 512, NULL, error);
			std::cout << "Error linking shader" << std::endl << error << std::endl;
		}
		glDetachShader(handle, vertexShader);
		glDetachShader(handle, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	Shader::~Shader()
	{
		glDeleteProgram(handle);
	}
	void Shader::Use()
	{
		glUseProgram(handle);
	}
	GLint Shader::GetAttributeHandle(const GLchar * name)
	{
		return glGetAttribLocation(handle, name);
	}
	GLint Shader::GetUniformHandle(const GLchar * name)
	{
		return glGetUniformLocation(handle, name);
	}
	void Shader::LoadShader(const GLchar * filename, GLint shadertype)
	{
		std::string shadercode;
		std::ifstream shaderfile;
		shaderfile.exceptions(std::ifstream::badbit);
		try
		{
			shaderfile.open(filename);
			std::stringstream shaderstream;
			shaderstream << shaderfile.rdbuf();
			shaderfile.close();
			shadercode = shaderstream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "error reading shader file" << filename << std::endl;
		}
		const GLchar* sourcecode = shadercode.c_str();
		if (shadertype == GL_VERTEX_SHADER)
		{
			vertexShader = glCreateShader(shadertype);
			glShaderSource(vertexShader, 1, &sourcecode, NULL);
			glCompileShader(vertexShader);
			GLint sucess;
			GLchar error[512];
			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &sucess);
			if (!sucess)
			{
				glGetShaderInfoLog(vertexShader, 512, NULL, error);
				std::cout << "Error compiling vertex shader" << std::endl << error << std::endl;
			}
		}
		if (shadertype == GL_FRAGMENT_SHADER)
		{
			fragmentShader = glCreateShader(shadertype);
			glShaderSource(fragmentShader, 1, &sourcecode, NULL);
			glCompileShader(fragmentShader);
			GLint sucess;
			GLchar error[512];
			glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &sucess);
			if (!sucess)
			{
				glGetShaderInfoLog(fragmentShader, 512, NULL, error);
				std::cout << "Error compiling fragment shader" << std::endl << error << std::endl;
			}
		}		
	}
