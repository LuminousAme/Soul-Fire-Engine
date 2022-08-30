//Soul Fire Engine by Ame Gilham, inspired by the Cherno's Hazel
//WindowsInput.cpp - source for the input handler implementation for microsoft windows

#include "SF_PCH.h"
#include "WindowsInput.h"
#include "SoulFire/Core/Application.h"

#include "SoulFire/Core/InputCodes.h"
#include "GLFW/glfw3.h"

namespace SoulFire {
	Input* Input::s_Instance = new WindowsInput();

	std::unordered_map<int, bool> WindowsInput::KeyWasPressedMap;
	std::unordered_map<int, bool> WindowsInput::KeyPressed;
	std::unordered_map<int, bool> WindowsInput::KeyHandled;
	std::unordered_map<int, bool> WindowsInput::MouseWasPressedMap;
	std::unordered_map<int, bool> WindowsInput::MousePressed;
	std::unordered_map<int, bool> WindowsInput::MouseHandled;

	bool WindowsInput::GetKeyImplementation(int keycode)
	{
		//check if the keyinputted currently exists in the map
		if (KeyWasPressedMap.find(keycode) == KeyWasPressedMap.end())
		{
			//if it doesn't, add it to the map (doing this here means we only add keys to the map if the user acutally wants to use them) 
			KeyWasPressedMap[keycode] = false;
			KeyHandled[keycode] = false;
			KeyPressed[keycode] = false;
		}

		//grab the window pointer
		auto window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindowPointer());
		//poll the state of the key
		auto keyState = glfwGetKey(window, keycode);

		//check if the key has been pressed
		if (keyState) {
			//if it has, set it's place in the map to true
			KeyWasPressedMap.at(keycode) = true;
			//return true as the key is being pressed
			return true;
		}

		//otherwise it hasn't been pressed so return false 
		return false;
	}

	bool WindowsInput::GetKeyDownImplementation(int keycode)
	{
		//check first if the key exists in the map
		if (KeyWasPressedMap.find(keycode) == KeyWasPressedMap.end())
		{
			//if it doesn't, pass it onto the getKey so it can create a place in the map, and check if it is being pressed
			if (GetKeyImplementation(keycode))
			{
				//if it sets the flag and return true that means the key has been pressed this frame
				KeyHandled.at(keycode) = true;
				KeyPressed.at(keycode) = true;
				return true;
			}
		}
		//if it does exist in the map, check if it was already handled this frame
		else if (KeyHandled.at(keycode)) {
			return true;
		}
		//if it does exist in the map and was not handled yet this frame, check if the value in the map is false and if the key is being pressed
		else if (GetKeyImplementation(keycode) && !KeyPressed.at(keycode)) {
			//if it is, then this is the first frame where it's being pressed so set the flags and return true
			KeyHandled.at(keycode) = true;
			KeyPressed.at(keycode) = true;

			return true;
		}
		//if it's not being pressed make sure the flag reflects that
		else if (!GetKeyImplementation(keycode)) {
			KeyPressed.at(keycode) = false;
		}

		//and return false as it's not being pressed
		return false;
	}

	bool WindowsInput::GetKeyUpImplementation(int keycode)
	{
		//check if the key is currently down, if it isn't, and it was marked as being down, that means it's been release this frame
		if (!GetKeyImplementation(keycode) && KeyWasPressedMap.at(keycode))
		{
			//return true to say it's been released
			return true;
		}
		//if not then the key is either still down, or was never put down in the first place, so just return false
		return false;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImplementation()
	{
		//grab the window pointer
		auto window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindowPointer());
		//grab the position
		double tempX, tempY;
		glfwGetCursorPos(window, &tempX, &tempY);

		//and return it
		return std::pair<float, float>((float)tempX, (float)tempY);
	}

	bool WindowsInput::GetMouseButtonImplementation(int button)
	{
		//check if the button inputted currently exists in the map
		if (MouseWasPressedMap.find(button) == MouseWasPressedMap.end())
		{
			//if it doesn't, add it to the map (doing this here means we only add buttons to the map if the user acutally wants to use them) 
			MouseWasPressedMap[button] = false;
			MouseHandled[button] = false;
			MousePressed[button] = false;
		}

		//grab the window pointer
		auto window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindowPointer());

		//check if the button has been pressed
		if (glfwGetMouseButton(window, button))
		{
			//if it has, set it's place in the map to true
			MouseWasPressedMap.at(button) = true;
			//return true as the button is being pressed
			return true;
		}
		//if it hasn't been pressed, return false
		return false;
	}

	bool WindowsInput::GetMouseButtonDownImplementation(int button)
	{
		//check first if the button exists in the map
		if (MouseWasPressedMap.find(button) == MouseWasPressedMap.end())
		{
			//if it doesn't, pass it onto the getMouseButton so it can create a place in the map, and check if it is being pressed
			if (GetMouseButtonImplementation(button))
			{
				//if it sets the flag and return true that means the key has been pressed this frame
				MouseHandled.at(button) = true;
				MousePressed.at(button) = true;
				return true;
			}
		}
		//if it does exist in the map, check if it was handleded already this frame
		else if (MouseHandled.at(button)) {
			//if it was, then return true
			return true;
		}
		//if it does exist in the map and was not yet handleded in this frame, check if the value in the map is false and if the button is being pressed
		else if (GetMouseButtonImplementation(button) && !MousePressed.at(button)) {
			//if it is, then this is the first frame where it's being pressed so set the flags and return true
			MouseHandled.at(button) = true;
			MousePressed.at(button) = true;

			return true;
		}
		//if it's not being pressed make sure the flag reflects that
		else if (!GetMouseButtonImplementation(button)) {
			MousePressed.at(button) = false;
		}

		//and return false as it's not being pressed
		return false;
	}

	bool WindowsInput::GetmouseButtonUpImplmentation(int button)
	{
		//check if the button is currently down, if it isn't, and it was marked as being down, that means it's been release this frame
		if (!GetMouseButtonImplementation(button) && MouseWasPressedMap.at(button))
		{
			//return true to say it's been released
			return true;
		}
		//if not then the button is either still down, or was never put down in the first place, so just return false
		return false;
	}

	void WindowsInput::ResetInputImplementation()
	{
		//grab the window pointer
		auto window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindowPointer());

		//reset each key
		for (auto& it : KeyWasPressedMap) {
			//if it's not currently being pressed, we need to reset the was pressed flag
			if (!glfwGetKey(window, static_cast<int>(it.first)))
				it.second = false;
		}
		for (auto& it : KeyHandled) {
			it.second = false;
		}

		//reset each mouse button
		for (auto& it : MouseWasPressedMap) {
			//if it's not currently being pressed, we need to reset the was pressed flag
			if (!glfwGetMouseButton(window, static_cast<int>(it.first)))
				it.second = false;
		}
		for (auto& it : MouseHandled) {
			it.second = false;
		}
	}
}