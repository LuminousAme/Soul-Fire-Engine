//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel 
//Transform.h - header file for the class that represents an objects' transform
#pragma once

#include "SF_PCH.h"

namespace SoulFire {
	class Transform {
	public:
		Transform();
		Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);
		~Transform();

		glm::vec3 GetPosition() const { return m_position; };
		void SetPosition(const glm::vec3& pos) { m_position = pos; dirty = true;  };

		glm::quat GetRotation() const { return m_rotation; };
		void SetRotation(const glm::quat& rot) { m_rotation = rot; dirty = true; };

		glm::vec3 GetScale() const { return m_scale; };
		void SetScale(const glm::vec3& scale) { m_scale = scale; dirty = true; };

		glm::mat4 GetTransform();

		void RotateRelative(glm::vec3 rotation);
		void RotateFixed(glm::vec3 rotation);

		void LookAt(glm::vec3 target, glm::vec3 up);
		void LookTowards(glm::vec3 direction, glm::vec3 up);

	private:
		glm::vec3 m_position;
		glm::quat m_rotation;
		glm::vec3 m_scale;

		glm::mat4 m_transform;

		bool dirty;
	};
}