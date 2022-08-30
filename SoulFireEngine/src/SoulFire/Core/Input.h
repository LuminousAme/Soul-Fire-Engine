//Soul Fire Engine by Ame Gilham, inspired by the Cherno's Hazel
//Input.h - header for the input handler class
#pragma once

#include "EngineCore.h"

namespace SoulFire {
	class SF_API Input {
	public:
		//get if a key is being pressed
		static bool GetKey(int keycode) {
			return s_Instance->GetKeyImplementation(keycode);
		}

		//get if a key has been pressed for it's first frame this frame
		static bool GetKeyDown(int keycode) {
			return s_Instance->GetKeyDownImplementation(keycode);
		}

		//checks if a key button has been released this frame
		static bool GetKeyUp(int keycode) {
			return s_Instance->GetKeyUpImplementation(keycode);
		}

		//returns the mouse position in screenspace
		static std::pair<float, float> GetMousePosition() {
			return s_Instance->GetMousePositionImplementation();
		}
		static float GetMouseX() {
			return GetMousePosition().first;
		}
		static float GetMouseY() {
			return GetMousePosition().second;
		}

		//checks if a mouse button is being pressed this frame
		static bool GetMouseButton(int button) {
			return s_Instance->GetMouseButtonImplementation(button);
		}

		//checks if a mouse button has been pressed for it's first frame this frame
		static bool GetMouseButtonDown(int button) {
			return s_Instance->GetMouseButtonDownImplementation(button);
		}

		//checks if a mouse button has been released this frame
		static bool GetMouseButtonUp(int button) {
			return s_Instance->GetmouseButtonUpImplmentation(button);
		}
		
		//resets input polling, needs to happen each frame
		static void ResetInput() {
			s_Instance->ResetInputImplementation();
		}

	protected:
		virtual bool GetKeyImplementation(int keycode) = 0;
		virtual bool GetKeyDownImplementation(int keycode) = 0;
		virtual bool GetKeyUpImplementation(int keycode) = 0;

		virtual std::pair<float, float> GetMousePositionImplementation() = 0;

		virtual bool GetMouseButtonImplementation(int button) = 0;
		virtual bool GetMouseButtonDownImplementation(int button) = 0;
		virtual bool GetmouseButtonUpImplmentation(int button) = 0;

		virtual void ResetInputImplementation() = 0;

	private:
		//singleton instance
		static Input* s_Instance;
	};
}