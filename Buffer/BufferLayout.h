#pragma once

#include<vector>


#include"Renderer/Renderer.h"




struct VertexBufferElement
{
	unsigned int type;
	unsigned int Count;
	unsigned char normalzide;

	static unsigned int getSize(unsigned int type )
	{
		switch (type)
		{
		case GL_FLOAT:                   return 4;
		case GL_UNSIGNED_INT:            return 4;
		case GL_BYTE:                    return 1;
		}
		return 0;

	}
};


class VertexbufferLayout
{
private:
	
	std::vector<VertexBufferElement> m_element;
	unsigned int m_stride;

public:
	
	VertexbufferLayout():m_stride(0){}

	template<typename T>
	void push(int count)
	{
		static_assert(false);
	}

	template<>
	void push<float>( int count)
	{
		m_element.push_back({GL_FLOAT,(unsigned int)count, GL_FALSE });
		m_stride += count*VertexBufferElement::getSize(GL_FLOAT);
	}

	template<>
    void push<int>( int count)
	{
		m_element.push_back({ GL_UNSIGNED_INT,(unsigned int)count,GL_FALSE });
		m_stride += count*VertexBufferElement::getSize(GL_UNSIGNED_INT);
	}

	template<>
	void push<unsigned char>(int count)
	{
		m_element.push_back({ GL_UNSIGNED_BYTE, (unsigned int)count, GL_TRUE});
		m_stride += count*VertexBufferElement::getSize(GL_BYTE);
	}

	inline const std::vector<VertexBufferElement> GetElement()const { return m_element; }
	inline unsigned int GetStride()const { return m_stride; }
};
