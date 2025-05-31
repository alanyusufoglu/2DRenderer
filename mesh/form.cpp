
#include"form.h"
#include<memory>
#include "glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

#include"Renderer/Renderer.h"
#include"ImGui/imgui.h"
#include"Buffer/BufferLayout.h"
#include"Texture/texture.h"


#include"ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"


namespace test {

    //--------------SQUARE----------------------------



    Square::Square() : m_translationA(200, 200, 0),
        m_Project(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), m_Color{ 0.8f, 0.3f, 0.8f, 1.0f } {

         float Vertexpotition[] = {

            0.0f,0.0f,      0.0f,0.0f,   //0
            100.0f,0.0f,    2.0f,0.0f,   //1
            0.0f,100.0f,    0.0f,2.0f,   //2
            100.0f,100.0f,  2.0f,2.0f   //3
         };

         int indicies[] =
         {
             2,0,1,
             1,3,2

         };
 
        m_VBO = std::make_unique<VertexBuffer>(Vertexpotition,4*4*sizeof(float));

        m_VAO = std::make_unique<VertexArray>();
        m_Shader = std::make_unique<Shader>("SRC/Shader/basic.shader");
        
        m_IBO = std::make_unique<IndexBuffer>(indicies,6);
        



        VertexbufferLayout layout;
        layout.push<float>(2);
        layout.push<float>(2);
        m_VAO->addBuffer(*m_VBO, layout);

       

        m_Shader->Bind();
        m_Shader->SetUniform4f("uColor", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
        m_Shader->UnBind();
     

        m_VAO->UnBind();
        m_VBO->UnBind();
        m_IBO->UnBind();

    }
 
    Square::~Square()
    {
    }

    void Square::OnUpdate(float DeltaTime)
    {
    }
    void Square::OnRenderer()
    {

        m_Shader->Bind();
        m_Shader->SetUniform4f("uColor", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
        m_Shader->UnBind();
        Renderer renderer;

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationA);
            glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale[0], scale[1], scale[2]));
            glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f)); // X 
            rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f));           // Y 
            rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f));          // Z 

            glm::mat4 MVP = m_Project * m_View * model * scaleMatrix * rotationMatrix;
            m_Shader->Bind();
            m_Shader->SetUniform4fv("u_Transform", MVP);

          
            renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
        }

    }

    void Square::OnImgui()
    {
        ImGui::SliderFloat3("floatA", &m_translationA.x, 0.0f, 960.0f);
        ImGui::ColorEdit4("RGBA", m_Color);
        ImGui::SliderFloat3("Scale", scale, 0.1f, 3.0f);
        ImGui::SliderFloat3("Rotation", rotation, 0.0f, 360.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f);
    }

    //------------------TRÝANGLE--------------------------------

    Triangle::Triangle() : m_translationA(400, 200, 0), m_Color{ 0.8f, 0.3f, 0.8f, 1.0f },
        m_Project(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))) {


        float Vertexpotition[] = {
              0.0f,0.0f,    0.0f,0.0f,  // 0
              100.0f,0.0f,  2.0f,0.0f,  // 1
              50.0f,100.0f, 1.0f,2.0f   // 2

        };

        int indicies[] =
        {
            2,0,1,
        };

        m_VAO = std::make_unique<VertexArray>();
        m_Shader = std::make_unique<Shader>("SRC/Shader/basic.shader");
        m_IBO = std::make_unique<IndexBuffer>(indicies, 3);


        m_VBO = std::make_unique<VertexBuffer>(Vertexpotition, 4 * 4 * sizeof(float));

        VertexbufferLayout layout;
        layout.push<float>(2);
        layout.push<float>(2);
        m_VAO->addBuffer(*m_VBO, layout);


        m_Shader->Bind();
        m_Shader->SetUniform4f("uColor", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);

        m_Shader->UnBind();
        m_VAO->UnBind();
        m_VBO->UnBind();
        m_IBO->UnBind();

    }

    Triangle::~Triangle()
    {
    }

    void Triangle::OnUpdate(float DeltaTime)
    {
    }
    void Triangle::OnRenderer()
    {

        m_Shader->Bind();
        m_Shader->SetUniform4f("uColor", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
        m_Shader->UnBind();
        Renderer renderer;

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationA);
            glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale[0], scale[1], scale[2]));
            glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f)); // X 
            rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f));           // Y 
            rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f));          // Z

            glm::mat4 MVP = m_Project * m_View * model * scaleMatrix * rotationMatrix;
            m_Shader->Bind();
            m_Shader->SetUniform4fv("u_Transform", MVP);
            renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
        }
    }


    void Triangle::OnImgui()
    {
        ImGui::SliderFloat3("floatA", &m_translationA.x, 0.0f, 960.0f);
        ImGui::ColorEdit4("RGBA", m_Color);
        ImGui::SliderFloat3("Scale", scale, 0.1f, 3.0f);
        ImGui::SliderFloat3("Rotation", rotation, 0.0f, 360.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f);
    }

    //-----------------CÝRCLE------------------------


      Circle::Circle() : m_translationA(600, 200, 0), m_Color{0.8f, 0.3f, 0.8f, 1.0f},
            m_Project(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
            m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))) {


            std::vector<Vertex> vertices;
            std::vector<unsigned int> indices;

            const int segments = 100;
            const float radius = 100.0f;
            glm::vec2 center = { 150.0f, 150.0f }; // ekranýn ortalarýna yakýn

            // Merkez vertex
            vertices.push_back({ center, {0.5f, 0.5f} });

            // Kenar vertexleri
            for (int i = 0; i <= segments; ++i) {
                float angle = 2.0f * glm::pi<float>() * i / segments;
                float x = center.x + radius * cos(angle);
                float y = center.y + radius * sin(angle);

                glm::vec2 texCoord = {
                    (cos(angle) * 0.5f) + 0.5f,
                    (sin(angle) * 0.5f) + 0.5f
                };

                vertices.push_back({ {x, y}, texCoord });
            }

            // Indexler (Triangle Fan: merkez + 2 kenar)
            for (int i = 1; i <= segments; ++i) {
                indices.push_back(0);       // merkez
                indices.push_back(i);       // þu kenar
                indices.push_back(i + 1);   // sonraki kenar
            }

            m_VAO = std::make_unique<VertexArray>();
            m_Shader = std::make_unique<Shader>("SRC/Shader/basic.shader");
            m_IBO = std::make_unique<IndexBuffer>(indices.data(), indices.size());


            m_VBO = std::make_unique<VertexBuffer>(vertices.data(), vertices.size() * sizeof(Vertex));

            VertexbufferLayout layout;
            layout.push<float>(2);
            layout.push<float>(2);
            m_VAO->addBuffer(*m_VBO, layout);


            m_Shader->Bind();
            m_Shader->SetUniform4f("uColor", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);

            m_Shader->UnBind();
            m_VAO->UnBind();
            m_VBO->UnBind();
            m_IBO->UnBind();

        }

        Circle::~Circle()
        {
        }

        void Circle::OnUpdate(float DeltaTime)
        {
        }
        void Circle::OnRenderer()
        {
            m_Shader->Bind();
            m_Shader->SetUniform4f("uColor", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
            m_Shader->UnBind();
            Renderer renderer;

            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationA);
                glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale[0], scale[1], scale[2]));
                glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f)); // X
                rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f));           // Y
                rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f));          // Z

                glm::mat4 MVP = m_Project * m_View * model* scaleMatrix* rotationMatrix;
                m_Shader->Bind();
                m_Shader->SetUniform4fv("u_Transform", MVP);
                renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
            }
        }


        void Circle::OnImgui()
        {




               
                ImGui::SliderFloat3("floatA", &m_translationA.x, 0.0f, 960.0f);
                ImGui::ColorEdit4("RGBA", m_Color);
                ImGui::SliderFloat3("Scale", scale, 0.1f, 3.0f);
                ImGui::SliderFloat3("Rotation", rotation, 0.0f, 360.0f);
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f);


        }

}
