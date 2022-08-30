//Soul Fire Engine by Ame Gilham, inspired by the Cherno's Hazel
//WindowsInput.h - header for the input handler implementation for microsoft windows
#pragma once

#include "SoulFire/Core/Input.h"

namespace SoulFire {
	class WindowsInput : public Input
	{
	protected:
		virtual bool GetKeyImplementation(int keycode) override;
		virtual bool GetKeyDownImplementation(int keycode) override;
		virtual bool GetKeyUpImplementation(int keycode) override;

		virtual std::pair<float, float> GetMousePositionImplementation() override;

		virtual bool GetMouseButtonImplementation(int button) override;
		virtual bool GetMouseButtonDownImplementation(int button) override;
		virtual bool GetmouseButtonUpImplmentation(int button) override;

		virtual void ResetInputImplementation() override;

	protected:
		//map of the booleans for if a key has been pressed
		static std::unordered_map<int, bool> KeyWasPressedMap;
		//map of boolean for if a key is being pressed
		static std::unordered_map<int, bool> KeyPressed;
		//map of booleans for if a key has been processed
		static std::unordered_map<int, bool> KeyHandled;

		//map of booleans for if a mouse button has been pressed
		static std::unordered_map<int, bool> MouseWasPressedMap;
		//map of boolean for if a mouse button is being pressed
		static std::unordered_map<int, bool> MousePressed;
		//map of boolean for if a mouse button has been processed
		static std::unordered_map<int, bool> MouseHandled;
	};
}