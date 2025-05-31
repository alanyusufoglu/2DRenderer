#include"Shader.h"
#include"Renderer/Renderer.h" 

#include<fstream>
#include<sstream>
#include<string>
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

ShaderSource Shader::ParseShader(const std::string& FilePath)
{
	std::ifstream stream(FilePath);
	if (!stream.is_open())
	{
		std::cout << "dosya acilmadi" << FilePath<<std::endl;		
	}

	enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			if (type != ShaderType::NONE)
				ss[(int)type] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompilerShader(const unsigned int& type,const std::string& shaderSource)
{
	GLCall(unsigned int id = glCreateShader(type));
	const char* src = shaderSource.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)malloc(length* sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "compile is failed" << (type == GL_VERTEX_SHADER) ? "vertex" : "fragment";
		std::cout<<"shader";
		std::cout << message;
		GLCall(glDeleteShader(id));
		return 0;
	}
	return id;
}
 unsigned int Shader::CreateShader(const std::string& vertexShader,const std::string& fragmentShader)
{
	 unsigned int program;
	 GLCall(program = glCreateProgram());
	 unsigned int vs = CompilerShader(GL_VERTEX_SHADER, vertexShader);
	 unsigned int fs = CompilerShader(GL_FRAGMENT_SHADER, fragmentShader);


	 GLCall(glAttachShader(program, vs));
	 GLCall(glAttachShader(program, fs));
	 GLCall(glLinkProgram(program));
	 GLCall(glValidateProgram(program));

	 int success;
	 glGetProgramiv(program, GL_LINK_STATUS, &success);
	 if (!success) {
		 char infoLog[512];
		 glGetProgramInfoLog(program, 512, NULL, infoLog);
		 std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	 }

	 GLCall(glDeleteShader(vs));
	 GLCall(glDeleteShader(fs));
	 return program;
}


Shader::Shader(const std::string& Filepath):m_filepath(Filepath),m_RendererId()
{
	ShaderSource source = ParseShader(Filepath);

	m_RendererId = CreateShader(source.VertexShaderSource, source.FragmentShaderSource);
}


Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererId));
}

void Shader::Bind()const
{
	GLCall(glUseProgram(m_RendererId));
}
void Shader::UnBind()const
{
	GLCall(glUseProgram(0));
}
 unsigned int Shader::GetLocation(const std::string& name)
{
	 if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		 return m_UniformLocationCache[name];

	 int location = glGetUniformLocation(m_RendererId, name.c_str());
	 if (location == -1)
		 std::cerr << "[Uyarý] Uniform '" << name << "' bulunamadý.\n";

	 m_UniformLocationCache[name] = location;
	 return location;
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	int loc = GetLocation(name);
	if (loc == -1)
		std::cerr << "[Uyarý] Uniform '" << name << "' shader içinde bulunamadý veya optimize edildi.\n";
	else
		GLCall(glUniform4f(loc, v0, v1, v2, v3));

}
void Shader::SetUniform1i(const std::string& name,  int value)
{
	int loc = GetLocation(name);
	if (loc == -1)
		std::cerr << "[Uyarý] Uniform '" << name << "' shader içinde bulunamadý veya optimize edildi.\n";
	else
		GLCall(glUniform1i(loc, value));

}
void Shader::SetUniform4fv(const std::string& name, glm::mat4& matrix)
{

		GLCall(glUniformMatrix4fv(GetLocation(name), 1, GL_FALSE, &matrix[0][0]));

}
void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
	GLint location = glGetUniformLocation(m_RendererId, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
}