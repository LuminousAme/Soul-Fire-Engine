//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel
//OthergraphicCameraController.h - header file for a class that handles interaction for debug orthographic cameras

#include "SF_PCH.h"
#include "OrthographicCameraController.h"

#include "SoulFire/Core/Input.h"
#include "SoulFire/Core/InputCodes.h"
#include "SoulFire/Core/HelperFunctions.h"
#include "Application.h"

namespace SoulFire {
	OrthograhpicCameraController::OrthograhpicCameraController(float aspectRatio)
		: m_aspectratio(aspectRatio), m_zoomlevel(1.0f), m_mousePos(glm::vec2(0.0f))
	{
		m_camera = Camera::Create(-m_aspectratio * m_zoomlevel, m_aspectratio * m_zoomlevel, -m_zoomlevel, m_zoomlevel, -1.0f, 1.0f);
		m_cameraMoveSpeedX = m_cameraMoveSpeedY * m_aspectratio;
	}

	void OrthograhpicCameraController::Update()
	{
		if (Input::GetMouseButtonDown(SF_MOUSE_BUTTON_2)) m_mousePos = Math::PairToVec2(Input::GetMousePosition());

		if (Input::GetMouseButton(SF_MOUSE_BUTTON_2)) {
			glm::vec2 currentMousePos = Math::PairToVec2(Input::GetMousePosition());
			
			glm::vec2 resolution;
			{
				int width, height;
				Window& wind = Application::GetApp().GetWindow();
				width = wind.GetWidth();
				height = wind.GetHeight();
				resolution = glm::vec2((float)width, (float)height);
			}

			glm::vec2 delta = (currentMousePos - m_mousePos) / resolution;

			delta.x *= -m_cameraMoveSpeedX * m_zoomlevel * Time::GetDeltaTime();
			delta.y *= m_cameraMoveSpeedY * m_zoomlevel * Time::GetDeltaTime();
			
			if (glm::length(delta) > 0.0f) {
				m_cameraPos += glm::vec3(delta.x, delta.y, 0.0f);
			}
			m_mousePos = currentMousePos;
		}

		if (m_camera->GetPosition() != m_cameraPos) m_camera->SetPosition(m_cameraPos);
	}

	void OrthograhpicCameraController::OnEvent(Event& ev)
	{
		EventDispatcher dispatcher(ev);
		dispatcher.Dispatch<MouseScrolledEvent>(SF_BIND_EVENT_FN(OrthograhpicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(SF_BIND_EVENT_FN(OrthograhpicCameraController::OnWindowResized));
	}

	bool OrthograhpicCameraController::OnMouseScrolled(MouseScrolledEvent& ev)
	{
		m_zoomlevel -= ev.GetOffsetY() * m_zoomspeed;
		m_zoomlevel = glm::max(m_zoomlevel, 0.25f);
		m_camera->UpdateProjection(-m_aspectratio * m_zoomlevel, m_aspectratio * m_zoomlevel, -m_zoomlevel, m_zoomlevel);
		return false;
	}

	bool OrthograhpicCameraController::OnWindowResized(WindowResizeEvent& ev)
	{
		m_aspectratio = (float)ev.GetWidth() / (float)ev.GetHeight();
		m_camera->UpdateProjection(-m_aspectratio * m_zoomlevel, m_aspectratio * m_zoomlevel, -m_zoomlevel, m_zoomlevel);
		return false;
	}
}