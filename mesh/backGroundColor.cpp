
#include"backGroundColor.h"

#include"Renderer/Renderer.h"
#include"ImGui/imgui.h"

namespace test {

	TestColor::TestColor():m_color{ 0.2f, 0.3f, 0.3f, 1.0f }
	{

    }

	TestColor::~TestColor()
	{

	}

	void TestColor::OnUpdate(float DeltaTime) 
	{

	}
	void TestColor::OnRenderer()
	{
		GLCall(glClearColor(m_color[0], m_color[1], m_color[2], m_color[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}


	void TestColor::OnImgui()
	{
		GLCall(ImGui::ColorEdit4("clear color", m_color));

	}

}