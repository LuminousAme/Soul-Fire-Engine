//SoulFire Engine by Ame Gilham, Inspired by The Cherno's Hazel
//LayerTree.cpp, source file for the class that represents a collection of engine layers

#include "SF_PCH.h"
#include "LayerTree.h"

namespace SoulFire {
	//constructor
	LayerTree::LayerTree()
	{
		m_InsertIndex = 0;
	}

	//desturctor
	LayerTree::~LayerTree()
	{
		//delete all of the layers
		for (Layer* layer : m_Layers) delete layer;
	}

	//adds a layer to the collection
	void LayerTree::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_InsertIndex, layer);
		m_InsertIndex++;
	}

	//remove a layer from the collection (without deleting it)
	void LayerTree::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
			m_InsertIndex--;
		}
	}

	//adds an overlay to the layers
	void LayerTree::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	//removes an overlay from the layers without deleting it
	void LayerTree::PopOverLay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
		}
	}
}

