//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel 
//Transform.cpp - source file for the class that represents an objects' transform

#include "SF_PCH.h"
#include "Transform.h"

namespace SoulFire {
	Transform::Transform()
		: m_position(glm::vec3(0.0f)), m_rotation(glm::quat(glm::radians(glm::vec3(0.0f)))), m_scale(glm::vec3(1.0f)),
		m_transform(glm::mat4(1.0f)), dirty(true)
	{
	}

	Transform::Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
		: m_position(pos), m_rotation(glm::quat(glm::radians(rot))), m_scale(scale),
		m_transform(glm::mat4(1.0f)), dirty(true)
	{
	}

	Transform::~Transform()
	{
	}

	glm::mat4 Transform::GetTransform()
	{
		if (dirty) {
			m_transform = glm::translate(m_position) *
				glm::toMat4(m_rotation) *
				glm::scale(m_scale);
			dirty = false;
		}

		return m_transform;
	}

	void Transform::RotateRelative(glm::vec3 rotation)
	{
		m_rotation = m_rotation * glm::quat(glm::radians(rotation));
		dirty = true;
	}

	void Transform::RotateFixed(glm::vec3 rotation)
	{
		m_rotation = glm::quat(glm::radians(rotation)) * m_rotation;
		dirty = true;
	}

	void Transform::LookAt(glm::vec3 target, glm::vec3 up)
	{
		m_rotation = glm::quatLookAt(target - m_position, up);
		dirty = true;
	}

	void Transform::LookTowards(glm::vec3 direction, glm::vec3 up)
	{
		m_rotation = glm::quatLookAt(direction, up);
		dirty = true;
	}
}