#include"VertexBuffer.h"
#include<Renderer/Renderer.h>

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GLCall(glGenBuffers(1, &m_RendererId));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
	GLCall(glBufferData(GL_ARRAY_BUFFER,  size , data, GL_DYNAMIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::Bind()const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
}
void VertexBuffer::UnBind()const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}