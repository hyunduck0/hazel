#pragma once

#include "Hazel/Layer.h"

#include "Hazel/Event/ApplicationEvent.h"
#include "Hazel/Event/KeyEvent.h"
#include "Hazel/Event/MouseEvent.h"

namespace Hazel
{
	class HAZEL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
//		virtual void OnUpdate() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();


	//	void OnEvent(Event& e);

	//private:
	//	bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
	//	bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
	//	bool OnMouseButtonMovedEvent(MouseMovedEvent& e);
	//	bool OnMouseButtonScrolledEvent(MouseScrolledEvent& e);
	//	
	//	bool OnKeyPressedEvent(KeyPressedEvent& e);
	//	bool OnKeyReleasedEvent(KeyReleasedEvent& e);
	//	bool OnKeyTypedEvent(KeyTypedEvent& e);
	//	bool OnWindowResizeEvent(WindowResizeEvent& e);
	private:
		float		m_Time = 0.0f;
	};
}