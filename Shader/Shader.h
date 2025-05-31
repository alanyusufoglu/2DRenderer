#pragma once

#include<iostream>
#include <unordered_map>
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

struct ShaderSource
{
	 std::string VertexShaderSource;
 std::string FragmentShaderSource;
};

class Shader
{

private:
	std::string m_filepath;
	 unsigned int m_RendererId;
	std::unordered_map<std::string, int> m_UniformLocationCache;

	
public:
	Shader(const std::string& Filepath);
	 ~Shader();
     void Bind()const;
	 void UnBind()const;

	 void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	 void SetUniform4fv(const std::string& name, glm::mat4& matrix);
	 void SetUniform1i(const std::string& name, int value);
	 void setMat4(const std::string& name, const glm::mat4& mat) const;
	 unsigned  int GetLocation(const std::string& name);

	 unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    unsigned int CompilerShader(const unsigned int& type, const std::string& shaderSource);
	 ShaderSource ParseShader(const std::string& FilePath);
};

