#pragma once

#include<vector>
#include<functional>
#include<iostream>
#include<glm/glm.hpp>

namespace test {

	class Test
	{

	public:


		Test(){}
		virtual ~Test() {}	
		virtual void OnUpdate(float DeltaTime) {}
		virtual void OnRenderer() {}
		virtual void OnImgui() {}
	};



	class TestMenu :public Test
	{
	public:

		TestMenu(Test*& CurrenTestPointer);
		~TestMenu(){}

		void OnImgui() override;

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout << "register test" << name;

			m_Test.push_back(std::pair(name,[](){ return new T();}));
		}


	private:


	 std::vector<std::pair<std::string, std::function<Test*()>>> m_Test;
		Test*& m_CurrenTest;
	};

}