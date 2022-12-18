//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//SceneCamera.cpp - source file for the camera for runtime scenes

#include "SF_PCH.h"
#include "SceneCamera.h"

namespace SoulFire {
	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}

	SceneCamera::~SceneCamera()
	{
	}

	void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
	{
		m_projectionType = ProjectionType::Orhtographic;
		m_orthoSize = size;
		m_orthoNear = nearClip;
		m_orthoFar = farClip;

		RecalculateProjection();
	}

	void SceneCamera::SetPerspective(float fov, float nearClip, float farClip)
	{
		m_projectionType = ProjectionType::Perspective;
		m_perspectiveFOV = fov;
		m_perspectiveNear = nearClip;
		m_perspectiveFar = farClip;

		RecalculateProjection();
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		m_aspectRatio = (float)width / (float)height;
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		if (m_projectionType == ProjectionType::Orhtographic) {
			float orthoLeft = -m_orthoSize * m_aspectRatio * 0.5f;
			float orthoRight = m_orthoSize * m_aspectRatio * 0.5f;
			float orthoBottom = -m_orthoSize * 0.5f;
			float orthoTop = m_orthoSize * 0.5f;

			m_projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, m_orthoNear, m_orthoFar);
		}
		else {
			m_projection = glm::perspective(m_perspectiveFOV, m_aspectRatio, m_perspectiveNear, m_perspectiveFar);
		}
	}

}