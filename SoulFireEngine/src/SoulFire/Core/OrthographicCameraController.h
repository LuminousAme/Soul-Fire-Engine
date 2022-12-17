//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//OthergraphicCameraController.h - header file for a class that handles interaction for debug orthographic cameras
#pragma once

#include "SoulFire/Renderer/Camera.h"

#include "SF_PCH.h"
#include "SoulFire/Events/ApplicationEvent.h"
#include "SoulFire/Events/MouseEvent.h"

namespace SoulFire {
	class OrthograhpicCameraController {
	public:
		OrthograhpicCameraController() = default;
		OrthograhpicCameraController(float aspectRatio); 

		void Update();
		void OnEvent(Event& ev);

		sptr<Camera> GetCamera() const { return m_camera; }

		void SetZoomLevel(const float& level) { m_zoomlevel = level; UpdateCamera(); }
		float GetZoomLevel() const { return m_zoomlevel; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& ev);
		bool OnWindowResized(WindowResizeEvent& ev);

		void UpdateCamera();
	private:
		float m_aspectratio;
		float m_zoomlevel;
		sptr<Camera> m_camera;

		glm::vec3 m_cameraPos = glm::vec3(0.0f);
		glm::vec2 m_mousePos;
		float m_cameraMoveSpeedY = 123.75;
		float m_cameraMoveSpeedX;
		float m_zoomspeed = 0.25f;
	};
}