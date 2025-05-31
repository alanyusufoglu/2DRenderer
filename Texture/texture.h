#pragma once

#include<iostream>

class Texture
{
private:
	 int m_width, m_height, BPP;
	unsigned int m_RendererId;
	std::string Filepath;
	unsigned char* LocalBuffer;



public:
	Texture(const std::string& path);
	~Texture();

	void Bind(const unsigned int slot=0)const;
	void UnBind()const;


	unsigned int GetWidth()const { return m_width; }
	unsigned int GetHeight()const { return m_height; }

};