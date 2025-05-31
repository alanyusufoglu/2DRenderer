#include<GL/glew.h>
#include<GLFW/glfw3.h>


#include<iostream>


#include<Renderer/Renderer.h>
#include"Buffer/IndexBuffer.h"
#include"Buffer/VertexBuffer.h"
#include"Shader/Shader.h"
#include"Buffer/BufferLayout.h"
#include"buffer/VertexArray.h"
#include"Texture/texture.h"
#include"mesh/backGroundColor.h"
#include"mesh/form.h"



#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include"ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"


    
const  int WIDTH = 960;
const  int HEIGHT = 540;


   
  
Renderer* render;


    int main() {
        if (!glfwInit()) {
            std::cerr << "GLFW baþlatýlamadý!" << std::endl;
            return -1;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "RENDERER", nullptr, nullptr);
        if (!window) {
            std::cerr << "Pencere oluþturulamadý!" << std::endl;
            glfwTerminate();
            return -1;
        }

        glfwMakeContextCurrent(window);

        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK) {
            std::cerr << "GLEW baþlatýlamadý!" << std::endl;
            glfwDestroyWindow(window);
            glfwTerminate();
            return -1;
        }
        glViewport(0, 0, WIDTH, HEIGHT);

      
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        const char* glsl_version = "#version 130";
        ImGui_ImplOpenGL3_Init(glsl_version);

        
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        std::cout << glGetString(GL_VERSION);;

        

        
        
       std::vector<std::pair<std::string, test::Test*>> dynamicTests;

        



      
        while (!glfwWindowShouldClose(window)) {

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

           
           
         
         
           
            ImGui::Begin("Mesh Panel");

           
            if (ImGui::Button("Square Ekle"))
                dynamicTests.emplace_back("Square", new test::Square());

            if (ImGui::Button("Triangle Ekle"))
                dynamicTests.emplace_back("Triangle", new test::Triangle());

           if (ImGui::Button("Circle Ekle"))
                dynamicTests.emplace_back("Circle", new test::Circle());
                
            ImGui::Separator();

            
            for (int i = 0; i < dynamicTests.size(); ++i)
            {
                auto& [name, test] = dynamicTests[i];

                ImGui::PushID(i);

              
                ImGui::Text("%s", name.c_str());
                ImGui::SameLine();

                if (ImGui::Button("Sil"))
                {
                    delete test;
                    dynamicTests.erase(dynamicTests.begin() + i);
                 
                    break; 
                }

               
                test->OnUpdate(0.0f);
                test->OnRenderer();
                 test->OnImgui();
                 ImGui::PopID();
            }
          
       
         
            ImGui::End();



            ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

           

            


            glfwSwapBuffers(window);
            glfwPollEvents();
        }


        glfwDestroyWindow(window);
        glfwTerminate();

        return 0;
    }


