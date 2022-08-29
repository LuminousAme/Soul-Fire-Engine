//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//Camera.cpp - source file for the camera classes
#pragma once

#include "SF_PCH.h"
#include "Camera.h"

namespace SoulFire {
	Camera::Camera()
		: m_view(glm::mat4()), m_projection(glm::mat4()), m_vp(glm::mat4()),
		m_position(glm::vec3(0.0f)), m_rotation(glm::quat(glm::radians(glm::vec3(0.0f, 0.0f, 0.0f)))),
		m_nearZ(0.01f), m_farZ(100.0f), viewdirty(true), projdirty(true)
	{
	}

	void Camera::LookAt(const glm::vec3& point, const glm::vec3& up)
	{
		glm::vec3 dir = point - m_position;
		LookTowards(dir, up);
	}

	void Camera::LookTowards(const glm::vec3& direction, const glm::vec3& up)
	{
		if (direction.length() == 0.0) SF_ENGINE_LOG_ASSERT(false, "Cannot look towards nothing!");
		if (up.length() == 0.0) SF_ENGINE_LOG_ASSERT(false, "Up direction must have a lenght!");

		m_rotation = glm::quatLookAt(direction, up);
		viewdirty = true;
	}

	void Camera::SetPosition(const glm::vec3& pos)
	{
		m_position = pos;
		viewdirty = true;
	}

	void Camera::RotateRelative(glm::vec3 rotation)
	{
		m_rotation = m_rotation * glm::quat(glm::radians(rotation));
		viewdirty = true;
	}

	void Camera::RotateFixed(glm::vec3 rotation)
	{
		m_rotation = glm::quat(glm::radians(rotation)) * m_rotation;
		viewdirty = true;
	}

	glm::mat4& Camera::GetVP()
	{
		bool dirty = false;
		if (viewdirty) {
			dirty = true;
			UpdateView();
		}
		if (projdirty) {
			dirty = true;
			UpdateProjection();
		}
		if (dirty) m_vp = m_projection * m_view;

		return m_vp;
	}

	Camera* Camera::Create(float left, float right, float bottom, float top, float nearClip, float farClip)
	{
		return new OrthographicCamera(left, right, bottom, top, nearClip, farClip);
	}

	Camera* Camera::Create(float fovDegrees, float aspectRatio, float nearClip, float farClip)
	{
		return new PrespectiveCamera(fovDegrees, aspectRatio, nearClip, farClip);
	}

	void Camera::UpdateView()
	{
		m_view = glm::inverse(glm::translate(m_position) * glm::toMat4(m_rotation));
		viewdirty = false;
	}

	OrthographicCamera::OrthographicCamera()
		: Camera(), m_left(0.0f), m_right(0.0f), m_bottom(0.0f), m_top(0.0f)
	{
	}

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float nearClip, float farClip)
		: Camera(), m_left(left), m_right(right), m_bottom(bottom), m_top(top)
	{
		m_nearZ = nearClip;
		m_farZ = farClip;
		projdirty = true;
	}

	void OrthographicCamera::UpdateProjection(float left, float right, float bottom, float top)
	{
		m_left = left;
		m_right = right;
		m_bottom = bottom;
		m_top = top;
		projdirty = true;
	}

	void OrthographicCamera::UpdateProjection(float fovDegrees, float aspectRatio)
	{
		SF_ENGINE_LOG_ASSERT(false, "Not implemented for othrographic cameras!");
	}

	void OrthographicCamera::UpdateProjection()
	{
		m_projection = glm::ortho(m_left, m_right, m_bottom, m_top, m_nearZ, m_farZ);
		projdirty = false;
	}

	PrespectiveCamera::PrespectiveCamera()
		: Camera(), m_fov(0.0f), m_aspectiveRatio(0.0f)
	{
	}

	PrespectiveCamera::PrespectiveCamera(float fovDegrees, float aspectRatio, float nearClip, float farClip)
		: Camera(), m_fov(fovDegrees), m_aspectiveRatio(aspectRatio)
	{
		m_nearZ = nearClip;
		m_farZ = farClip;
		projdirty = true;
	}

	void PrespectiveCamera::UpdateProjection(float left, float right, float bottom, float top)
	{
		SF_ENGINE_LOG_ASSERT(false, "Not implemented for prespective cameras!");
	}

	void PrespectiveCamera::UpdateProjection(float fovDegrees, float aspectRatio)
	{
		m_fov = fovDegrees;
		m_aspectiveRatio = aspectRatio;
		projdirty = true;
	}

	void PrespectiveCamera::UpdateProjection()
	{
		m_projection = glm::perspective(glm::radians(m_fov), m_aspectiveRatio, m_nearZ, m_farZ);
		projdirty = false;
	}
}