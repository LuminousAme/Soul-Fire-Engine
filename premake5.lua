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
IncludeDirTable["stb_image"] = "SoulFireEngine/dependencies/stb_image"
IncludeDirTable["ENTT"] = "SoulFireEngine/dependencies/ENTT/include"
IncludeDirTable["yaml_cpp"] = "SoulFireEngine/dependencies/yaml_cpp/include"

-- include the glfw premake
group "Dependencies"
	include "SoulFireEngine/dependencies/glfw3"
	include "SoulFireEngine/dependencies/Glad"
	include "SoulFireEngine/dependencies/Imgui"
	include "SoulFireEngine/dependencies/yaml_cpp"

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
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/dependencies/stb_image/**.h",
		"%{prj.name}/dependencies/stb_image/**.cpp"
	}

	defines 
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs 
	{
		"%{prj.name}/src",
		"%{prj.name}/dependencies/spdlog/include",
		"%{IncludeDirTable.GLFW}",
		"%{IncludeDirTable.GLAD}",
		"%{IncludeDirTable.GLM}",
		"%{IncludeDirTable.ImGui}",
		"%{IncludeDirTable.stb_image}",
		"%{IncludeDirTable.ENTT}",
		"%{IncludeDirTable.yaml_cpp}"
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

project "SoulFireEditor"
	location "SoulFireEditor"
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
		"%{IncludeDirTable.GLM}",
		"%{IncludeDirTable.ENTT}",
		"%{IncludeDirTable.yaml_cpp}"
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
		"%{IncludeDirTable.GLM}",
		"%{IncludeDirTable.ENTT}"
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