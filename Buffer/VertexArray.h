#pragma once



#include"Buffer/VertexBuffer.h"

class VertexbufferLayout;



class VertexArray
{
private:
	unsigned int m_RendererId;
public:
	VertexArray();
	~VertexArray();
	void Bind()const;
	void UnBind()const;

	void addBuffer(VertexBuffer& vb, VertexbufferLayout& layout);
};