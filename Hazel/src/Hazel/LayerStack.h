#pragma once

#include "Hazel/Core.h"
#include "Layer.h"

namespace Hazel
{
	typedef std::vector<Layer*> Veclayer;
	typedef std::vector<Layer*>::iterator LayerIter;

	class HAZEL_API LayerStack
	{
	public :
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		LayerIter begin() { return m_Layers.begin(); }
		LayerIter end() { return m_Layers.end(); }
	private:
		Veclayer m_Layers;
		//LayerIter m_LayerInsert;
		unsigned int m_LayerInsertIndex = 0;
	};
}