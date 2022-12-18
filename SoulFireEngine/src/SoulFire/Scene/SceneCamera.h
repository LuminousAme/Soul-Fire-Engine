//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//SceneCamera.h - header file for the camera for runtime scenes
#pragma once

#include "SoulFire/Renderer/Camera.h"

namespace SoulFire {
	class SceneCamera : public RuntimeCamera {
	public:
		enum class ProjectionType { Orhtographic = 0, Perspective = 1 };

	public:
		SceneCamera();
		virtual ~SceneCamera();

		void SetOrthographic(float size, float nearClip, float farClip);
		void SetPerspective(float fov, float nearClip, float farClip);

		void SetViewportSize(uint32_t width, uint32_t height);

		float GetOrthoSize() const { return m_orthoSize; }
		void SetOrthoSize(float size) { m_orthoSize = size; RecalculateProjection(); }
		float GetOrthoNear() const { return m_orthoNear; }
		void SetOrthoNear(float nearClip) { m_orthoNear = nearClip; RecalculateProjection(); }
		float GetOrthoFar() const { return m_orthoFar; }
		void SetOrthoFar(float farClip) { m_orthoFar = farClip; RecalculateProjection(); }

		float GetPerspectiveVerticalFOV() const { return m_perspectiveFOV; }
		void SetPerspectiveVerticalFOV(float FOV) { m_perspectiveFOV = FOV; RecalculateProjection(); }
		float GetPerspectiveNear() const { return m_perspectiveNear; }
		void SetPerspectiveNear(float nearClip) { m_perspectiveNear = nearClip; RecalculateProjection(); }
		float GetPerspectiveFar() const { return m_perspectiveFar; }
		void SetPerspectiveFar(float farClip) { m_perspectiveFar = farClip; RecalculateProjection(); }

		ProjectionType GetProjectionType() const { return m_projectionType; }
		void SetProjectionType(ProjectionType type) { m_projectionType = type; RecalculateProjection(); }
	private:
		void RecalculateProjection();
	private:
		ProjectionType m_projectionType = ProjectionType::Orhtographic;

		float m_orthoSize = 10.0f;
		float m_orthoNear = -1.0f, m_orthoFar = 1.0f;

		float m_perspectiveFOV = glm::radians(45.0f);
		float m_perspectiveNear = 0.01f, m_perspectiveFar = 1000.0f;

		float m_aspectRatio = 0.0f;
	};
}