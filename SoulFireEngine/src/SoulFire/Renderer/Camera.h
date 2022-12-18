//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Camera.h - header file for the camera classes
#pragma once

#include "SF_PCH.h"

namespace SoulFire {
	class Camera {
	public:
		Camera();
		virtual ~Camera() {};

		void LookAt(const glm::vec3& point, const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f));
		void LookTowards(const glm::vec3& direction, const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f));

		glm::vec3 GetPosition() const { return m_position; }
		void SetPosition(const glm::vec3& pos);

		virtual void UpdateProjection(float left, float right, float bottom, float top) = 0;
		virtual void UpdateProjection(float fovDegrees, float aspectRatio) = 0;

		void SetNearPlane(const float& nearClip) { m_nearZ = nearClip; projdirty = true; }
		void SetFarPlane(const float& farClip) { m_farZ = farClip; projdirty = true; }

		void RotateRelative(glm::vec3 rotation);
		void RotateFixed(glm::vec3 rotation);

		glm::mat4& GetVP();

		static sptr<Camera> Create(float left, float right, float bottom, float top, float nearClip, float farClip);
		static sptr<Camera> Create(float fovDegrees, float aspectRatio, float nearClip, float farClip);
	protected:
		virtual void UpdateProjection() = 0;
		void UpdateView();
	protected:
		glm::mat4 m_view;
		glm::mat4 m_projection;
		glm::mat4 m_vp;

		glm::vec3 m_position;
		glm::quat m_rotation;

		float m_nearZ;
		float m_farZ;

		bool viewdirty;
		bool projdirty;
	};

	class OrthographicCamera : public Camera {
	public:
		OrthographicCamera();
		OrthographicCamera(float left, float right, float bottom, float top, float nearClip, float farClip);
		virtual ~OrthographicCamera() {};

		void UpdateProjection(float left, float right, float bottom, float top) override;
		void UpdateProjection(float fovDegrees, float aspectRatio)override;
	protected:
		void UpdateProjection() override;
	private:
		float m_left;
		float m_right;
		float m_bottom; 
		float m_top;
	};

	class PrespectiveCamera : public Camera {
	public:
		PrespectiveCamera();
		PrespectiveCamera(float fovDegrees, float aspectRatio, float nearClip, float farClip);
		virtual ~PrespectiveCamera() {};

		void UpdateProjection(float left, float right, float bottom, float top) override;
		void UpdateProjection(float fovDegrees, float aspectRatio)override;
	protected:
		void UpdateProjection() override;
	private:
		float m_aspectiveRatio;
		float m_fov;
	};

	class RuntimeCamera {
	public:
		RuntimeCamera() = default;
		RuntimeCamera(const glm::mat4& projection)
			: m_projection(projection) {}

		virtual ~RuntimeCamera() = default;

		const glm::mat4& GetProjection() const { return m_projection; }
	protected:
		glm::mat4 m_projection = glm::mat4(1.0f);
	};
}