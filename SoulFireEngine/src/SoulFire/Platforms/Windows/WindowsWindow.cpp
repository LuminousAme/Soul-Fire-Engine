//SoulFire Engine by Ame Gilham, inspired by the Cherno's Hazel
//WindowsWindow.cpp - source file for soul fire windows on the Microsoft windows platform

#include "SF_PCH.h"
#include "WindowsWindow.h"
#include <glad/glad.h>

//event types
#include "SoulFire/Events/Event.h"
#include "SoulFire/Events/ApplicationEvent.h"
#include "SoulFire/Events/MouseEvent.h"
#include "SoulFire/Events/KeyEvent.h"


namespace SoulFire {

	static bool s_GLFWInitialized = false;

	//glfw error callback and logging
	static void GLFWErrorCallback(int errorCode, const char* errorDesc) {
		//just logs the error
		SF_ENGINE_LOG_ERROR("GLFW Error ({0}): {1}", errorCode, errorDesc);
	}

	//overload the create function to return a new window pointer
	Window* Window::CreateNewWindow(const WindowDetails& details)
	{
		return new WindowsWindow(details);
	}

	//window constructor
	WindowsWindow::WindowsWindow(const WindowDetails& details)
	{
		//starts up the window
		Startup(details);
	}

	//destructor
	WindowsWindow::~WindowsWindow()
	{
		//shuts down the window
		Shutdown();
	}

	//update every frame
	void WindowsWindow::Update()
	{
		//have glfw check for events
		glfwPollEvents();

		m_context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool vysncOn)
	{
		if (vysncOn)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_data.vysnc = vysncOn;
	}

	bool WindowsWindow::GetVSync() const
	{
		return m_data.vysnc;
	}

	const char* WindowsWindow::GetClipBoardText()
	{
		return glfwGetClipboardString(m_window);
	}

	void WindowsWindow::SetClipBoardText(const char* text)
	{
		glfwSetClipboardString(m_window, text);
	}

	//inits the window
	void WindowsWindow::Startup(const WindowDetails& details)
	{
		//copy data
		m_data.m_title = details.m_Name;
		m_data.m_width = details.m_Width;
		m_data.m_height = details.m_Height;

		//log the fact that the window is being created
		SF_ENGINE_LOG_INFO("Creating Window: {0}, {1} x {2}", details.m_Name, details.m_Width, details.m_Height);

		//if glfw is not already initialized then initalize it 
		if (!s_GLFWInitialized) {
			//TO Do: glfw terminate on system shutdown

			//init it and check if it worked
			int setupWorked = glfwInit();
			SF_ENGINE_LOG_ASSERT(setupWorked, "GLFW initalization failed!");
			//set up glfw error logging
			glfwSetErrorCallback(GLFWErrorCallback);

			//save the fact that it is initliazed
			s_GLFWInitialized = true;
		}

		//create the window, set it as the current context, send in the data as a user pointer, and turn vsync on
		m_window = glfwCreateWindow((int)m_data.m_width, (int)m_data.m_height, m_data.m_title.c_str(), nullptr, nullptr);
		m_context = new OpenGLContext(m_window);
		m_context->Init();

		SetVSync(true);
		glfwSetWindowUserPointer(m_window, &m_data);
		// Setup GLFW callbacks

		//resize event
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
			//grab the user pointer, cast and dereference it
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			//store some data, make the event, and dispatch it
			data.m_width = width;
			data.m_height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		//close event
		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
			//grab the user pointer, cast and dereference it
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			//make the event and dispatch it 
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		//char event callback
		glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int key) {
			//grab the user pointer, cast and dereference it
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(key);
			data.EventCallback(event);
		});
		
		//key event
		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			//grab the user pointer, cast and dereference it
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			//make the event and dispatch it 
			if (action == GLFW_PRESS) {
				KeyPressedEvent event(key, 0);
				data.EventCallback(event);
			}
			else if (action == GLFW_RELEASE) {
				KeyReleasedEvent event(key);
				data.EventCallback(event);
			}
			else if (action == GLFW_REPEAT) {
				KeyPressedEvent event(key, 1);
				data.EventCallback(event);
			}
		});

		//mouse button callbacks
		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int key, int action, int mods) {
			//grab the user pointer, cast and dereference it
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			//make the event and dispatch it 
			if (action == GLFW_PRESS) {
				MouseButtonPressedEvent event(key);
				data.EventCallback(event);
			}
			else if (action == GLFW_RELEASE) {
				MouseButtonReleasedEvent event(key);
				data.EventCallback(event);
			}
		});

		//mouse scroll callbacks
		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset) {
			//grab the user pointer, cast and dereference it
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			//make the event and dispatch it 
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		//mouse move callbacks
		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos) {
			//grab the user pointer, cast and dereference it
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			//make the event and dispatch it 
			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}

	//when the window is shuting down
	void WindowsWindow::Shutdown()
	{
		//destroy the window
		glfwDestroyWindow(m_window);
		delete m_context;
	}
}