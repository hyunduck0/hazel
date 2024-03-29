#include <Hazel.h>

#include "imgui/imgui.h"

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
		//auto cam = camera(5.0f, { 0.5, 0.5f });

	}

	void OnUpdate() override
	{
		//HZ_INFO("examplelayer: update");

		if (Hazel::Input::IsKeyPressed(HZ_KEY_TAB))
			HZ_TRACE("Tab Key is Pressed(poll)!");

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::End();
	}

	void OnEvent(Hazel::Event& event) override
	{
		//HZ_TRACE("{0}", event);
		if (event.GetEventType() == Hazel::EventType::KeyPressed)
		{
			Hazel::KeyPressedEvent & e = (Hazel::KeyPressedEvent&)event;

			if (e.GetKeyCode() == HZ_KEY_TAB)
				HZ_TRACE("Tab key is Pressed(event)!");

			HZ_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Hazel::Application

{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer);
		//PushLayer(new Hazel::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}