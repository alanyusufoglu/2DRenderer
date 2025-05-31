#include"mesh.h"
#include"ImGui/imgui.h"


namespace test
{
	TestMenu::TestMenu(Test*& CurrenTestPointer):m_CurrenTest(CurrenTestPointer)
	{

	}

	

	void TestMenu::OnImgui()
	{
		for (auto& Test : m_Test)
		{
			if (ImGui::Button(Test.first.c_str()))
			m_CurrenTest=Test.second();
			
		}



	}




}