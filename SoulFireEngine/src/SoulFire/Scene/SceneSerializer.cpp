//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//SceneSerializer.cpp - source file for the class that handles serializing scenes

#include "SF_PCH.h"
#include "SceneSerializer.h"
#include <yaml-cpp/yaml.h>
#include <fstream>
#include "Components.h"
#include "Entity.h"

namespace SoulFire {
	SceneSerializer::SceneSerializer(const sptr<Scene>& scene)
		: m_scene(scene)
	{
	}

	static void SerializeEntity(YAML::Emitter& out, Entity entity) {
		out << YAML::BeginMap; //Entity map
		out << YAML::Key << "Entity" << YAML::Value << "13541351536413513"; //replace number with GUID when implemented

		//Info component 
		if (entity.HasComponent<InfoComponent>()) {
			out << YAML::Key << "InfoComponent";
			out << YAML::BeginMap; //Info Component map

			auto& component = entity.GetComponent<InfoComponent>();
			out << YAML::Key << "Name" << YAML::Value << component.m_name;
			out << YAML::Key << "Tag" << YAML::Value << component.m_tag;

			out << YAML::EndMap; //Info component map
		}

		out << YAML::EndMap; //Entity map
	}

	void SceneSerializer::Serialize(const std::string& filepath)
	{
		YAML::Emitter out;
		out << YAML::BeginMap; //scene map
		out << YAML::Key << "Scene" << YAML::Value << "Untitled";

		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
		m_scene->m_registry.each([&](auto entityID) {
			Entity entity = Entity(entityID, m_scene.get());
			if (!entity) return;

			SerializeEntity(out, entity);
		});
		out << YAML::EndSeq;
		out << YAML::EndMap; //scene map

		std::ofstream fout(filepath);
		fout << out.c_str();
 	}

	void SceneSerializer::SerializeRuntime(const std::string& filepath)
	{
		SF_ENGINE_LOG_ASSERT(false, "Serialize runtime not yet implemented");
	}

	bool SceneSerializer::DeSerialize(const std::string& filepath)
	{
		return false;
	}

	bool SceneSerializer::DeSerializeRuntime(const std::string& filepath)
	{
		SF_ENGINE_LOG_ASSERT(false, "Deserialize runtime not yet implemented");
		return false;
	}
}