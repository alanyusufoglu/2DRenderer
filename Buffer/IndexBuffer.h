#pragma once

class IndexBuffer
{
private:
	unsigned int m_RendererId;
	unsigned int m_count;

public:
	inline unsigned int GetCount()const { return m_count; }
	IndexBuffer(const void* data, unsigned int count );
	~IndexBuffer();
	void Bind()const;
	void UnBind()const ;
};