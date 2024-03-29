#include "hzpch.h"
#include "Application.h"

#include "Log.h"

//#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Input.h"


namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::s_Instance = nullptr;


	Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance, "Application already exsists!!")
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
	
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

//		unsigned int id;
//		glGenVertexArrays(1, &id);

		//m_ImGuiLayer = std::unique_ptr<ImGuiLayer>();

		m_ImGuiLayer = new ImGuiLayer();
		PushLayer(m_ImGuiLayer);
	
		// vertex array
		// vertex buffer
		// index buffer

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f, 
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		unsigned int Indices[3] = { 0, 1, 2 };

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position , 1.0);
			}
			
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}


	Application::~Application()
	{
	}
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		//HZ_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.GetHandle())
				break;
		}

	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	


	void Application::Run()
	{

		//WindowResizeEvent e(1280, 720);
		////HZ_TRACE(e);

		//if (e.isInCategory(Hazel::EventCategoryApplication))
		//{
		//	HZ_TRACE(e);
		//}

		//if (e.isInCategory(EventCategoryInput))
		//{
		//	HZ_TRACE(e);
		//}

		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);


			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();

			m_ImGuiLayer->End();

//			auto[x, y] = Input::GetMousePosition();
//			HZ_CORE_TRACE("{0}, {1}", x, y);

			m_Window->OnUpdate();
		}
	}
}

