#pragma once


#include"mesh.h"



namespace test {


	class TestColor : public Test
	{
		public:

			TestColor();
			~TestColor();

			void OnUpdate(float Deltatime) override;
			void OnRenderer() override;
			void OnImgui() override;

			private:

				float m_color[4];




	};





}