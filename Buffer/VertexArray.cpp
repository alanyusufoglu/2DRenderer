

#include"VertexArray.h"
#include<Renderer/Renderer.h>
#include"Buffer/BufferLayout.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererId));
};
VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererId));
}
void VertexArray::addBuffer(VertexBuffer& vb, VertexbufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElement();
	unsigned int offset=0;
	vb.Bind();
	for (unsigned int i = 0; i < elements.size(); i++)
	{	
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.Count,element.type,element.normalzide,layout.GetStride(),(const void*)(uintptr_t)offset));

		offset += element.Count * VertexBufferElement::getSize(element.type);
	}
}

void VertexArray::Bind()const
{
	GLCall(glBindVertexArray(m_RendererId));
}

void  VertexArray::UnBind()const
{
	GLCall(glBindVertexArray(0));
}