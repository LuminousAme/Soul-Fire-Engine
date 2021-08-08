//SoulFire Engine by Ame Gilham, Inspired by The Cherno's Hazel
//LayerTree.h, class that represents a collection of engine layers

#pragma once

#include "SoulFire/EngineCore.h"
#include "Layer.h"

namespace SoulFire {
	//class for a collection of layers
	class SF_API LayerTree
	{
	public:
		//constructor and destructor
		LayerTree();
		~LayerTree();

		//function to add and remove layers
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverLay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		//container for the layers
		std::vector<Layer*> m_Layers;
		std::vector<Layer*>::iterator m_InsertPoint;
	};
}