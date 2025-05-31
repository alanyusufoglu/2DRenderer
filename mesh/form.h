#pragma once


#include"mesh.h"
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

	



	class Square: public Test
	{
		public:
			Square();
			~Square();

			void OnUpdate(float Deltatime) override;
			void OnRenderer() override;
			void OnImgui() override;
			
			private:
		    std::unique_ptr<VertexArray> m_VAO;
			std::unique_ptr<IndexBuffer> m_IBO;
		    std::unique_ptr<Shader> m_Shader;
			std::unique_ptr<Texture> m_Texture;
			std::unique_ptr<VertexBuffer> m_VBO;
		

			glm::vec3 m_translationA;
			float scale[3] = { 1.0f, 1.0f, 1.0f };
			float rotation[3] = { 0.0f, 0.0f, 0.0f };
			float m_Color[4];
			glm::mat4 m_Project, m_View;

		

	};


	class Triangle : public Test
	{
	public:

		Triangle();
		~Triangle();

		void OnUpdate(float Deltatime) override;
		void OnRenderer() override;
		void OnImgui() override;

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr<Shader> m_Shader;
		float m_Color[4];
		std::unique_ptr<VertexBuffer> m_VBO;
		glm::vec3 m_translationA;
		float scale[3] = { 1.0f, 1.0f, 1.0f };
		float rotation[3] = { 0.0f, 0.0f, 0.0f };
		
		glm::mat4 m_Project, m_View;
	};

	class Circle : public Test
	{
	public:

		struct Vertex {
			glm::vec2 Position;
			glm::vec2 TexCoord;
		};

		Circle();
		~Circle();

		void OnUpdate(float Deltatime) override;
		void OnRenderer() override;
		void OnImgui() override;

	private:
		std::unique_ptr<VertexArray> m_VAO;
		float m_Color[4];
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr<Shader> m_Shader;

		std::unique_ptr<VertexBuffer> m_VBO;
		glm::vec3 m_translationA;
		float scale[3] = { 1.0f, 1.0f, 1.0f };
		float rotation[3] = { 0.0f, 0.0f, 0.0f };

		glm::mat4 m_Project, m_View;
	};





}