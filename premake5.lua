-- p

-- Get the root directionary we are calling premake from
local rootdir = path.getabsolute(_WORKING_DIR)

workspace "Soul Fire"
	architecture "x64"

	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

outputdir = "%{cfg.buildcgf}-%{cfg.system}-%{cfg.architecture}"

IncludeDirTable = {}
IncludeDirTable["GLFW"] = "SoulFireEngine/dependencies/glfw3/include"
IncludeDirTable["GLAD"] = "SoulFireEngine/dependencies/Glad/include"
IncludeDirTable["GLM"] = "SoulFireEngine/dependencies/glm/include"
IncludeDirTable["ImGui"] = "SoulFireEngine/dependencies/Imgui"

-- include the glfw premake
group "Dependencies"
	include "SoulFireEngine/dependencies/glfw3"
	include "SoulFireEngine/dependencies/Glad"
	include "SoulFireEngine/dependencies/Imgui"

group ""

project "SoulFireEngine"
	location "SoulFireEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("bin/" .. outputdir.. "/%{prj.name}")
	objdir ("obj/" .. outputdir.. "/%{prj.name}")

	pchheader "SF_PCH.h"
	pchsource "SoulFireEngine/src/SF_PCH.cpp"
 
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs 
	{
		"%{prj.name}/src",
		"%{prj.name}/dependencies/spdlog/include",
		"%{IncludeDirTable.GLFW}",
		"%{IncludeDirTable.GLAD}",
		"%{IncludeDirTable.GLM}",
		"%{IncludeDirTable.ImGui}"
	}

	links {
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"

		systemversion "latest"

		defines 
		{
			"SF_PLATFORM_WINDOWS",
			"SF_BUILDING_DLL"
		}

	filter "configurations:Debug"
		defines "SF_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "SF_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Distribution"
		defines "SF_DISTRIBUTION"
		runtime "Release"
		optimize "On"



project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("bin/" .. outputdir.. "/%{prj.name}")
	objdir ("obj/" .. outputdir.. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs 
	{
		"SoulFireEngine/dependencies/spdlog/include",
		"SoulFireEngine/src",
		"SoulFireEngine/dependencies",
		"%{IncludeDirTable.GLM}"
	}

	links
	{
		"SoulFireEngine"
	}

	filter "system:windows"
		systemversion "latest"

		defines 
		{
			"SF_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "SF_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "SF_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Distribution"
		defines "SF_DISTRIBUTION"
		runtime "Release"
		optimize "On"