//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//SceneSerializer.h - header file for the class that handles serializing scenes
#pragma once

#include "Scene.h"

namespace SoulFire {
	class SceneSerializer {
	public:
		SceneSerializer(const sptr<Scene>& scene);

		void Serialize(const std::string& filepath);
		void SerializeRuntime(const std::string& filepath);

		bool DeSerialize(const std::string& filepath);
		bool DeSerializeRuntime(const std::string& filepath);
	private:
		sptr<Scene> m_scene;
	};
}