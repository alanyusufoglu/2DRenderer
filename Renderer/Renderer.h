

#pragma once


#include <GL/glew.h>
#include<GLFW/glfw3.h>
#include "buffer/IndexBuffer.h"
#include "buffer/VertexBuffer.h"
#include "Shader/Shader.h"
#include "Buffer/BufferLayout.h"
#include "buffer/VertexArray.h"

#define ASSERT(x)  if (!(x)) __debugbreak()
#define GLCall(x)  GLClearError(); \
    x; \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{

public:

    void Draw( const VertexArray& va,  const IndexBuffer& ib,const Shader& shader)const;
 
    void clear();
    
  
};


