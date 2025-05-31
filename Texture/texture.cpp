#include"texture.h"
#include"stb/stb.h"
#include"Renderer/Renderer.h"



Texture::Texture(const std::string& path ):m_RendererId(0),m_width(0),m_height(0),
Filepath(path),LocalBuffer(nullptr),BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	LocalBuffer = stbi_load(Filepath.c_str(), &m_width, &m_height, &BPP, 4);
	LocalBuffer = stbi_load(Filepath.c_str(), &m_width, &m_height, &BPP, 4);
	if (LocalBuffer == nullptr) {
		std::cout << "Texture yükleme hatasý: " << Filepath << std::endl;
		std::cerr << "STB Error: " << stbi_failure_reason() << std::endl;
	}

	GLCall(glGenTextures(1,&m_RendererId));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererId));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, LocalBuffer));

	
	stbi_image_free(LocalBuffer);

	


}
Texture::~Texture()
{
	GLCall(glDeleteTextures(1,&m_RendererId));

}

void Texture::Bind(const unsigned int slot)const
{

	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D,m_RendererId));

}

void Texture::UnBind()const
{

	glBindTexture(GL_TEXTURE_2D, 0);


}