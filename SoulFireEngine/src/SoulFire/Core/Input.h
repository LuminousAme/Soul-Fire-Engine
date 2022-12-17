//Soul Fire Engine by Ame Gilham, inspired by the Cherno's Hazel
//Input.h - header for the input handler class
#pragma once

#include "EngineCore.h"

namespace SoulFire {
	class SF_API Input {
	public:
		//get if a key is being pressed
		static bool GetKey(int keycode);

		//get if a key has been pressed for it's first frame this frame
		static bool GetKeyDown(int keycode);

		//checks if a key button has been released this frame
		static bool GetKeyUp(int keycode);

		//returns the mouse position in screenspace
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();

		//checks if a mouse button is being pressed this frame
		static bool GetMouseButton(int button);

		//checks if a mouse button has been pressed for it's first frame this frame
		static bool GetMouseButtonDown(int button);

		//checks if a mouse button has been released this frame
		static bool GetMouseButtonUp(int button);
		
		//resets input polling, needs to happen each frame
		static void ResetInput();
	};
}