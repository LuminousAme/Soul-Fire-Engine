-- p

-- Get the root directionary we are calling premake from
local rootdir = path.getabsolute(_WORKING_DIR)

workspace "Soul Fire"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

outputdir = "%{cfg.buildcgf}-%{cfg.system}-%{cfg.architecture}"

IncludeDirTable = {}
IncludeDirTable["GLFW"] = "SoulFireEngine/dependencies/glfw3/include"

-- include the glfw premake
include "SoulFireEngine/dependencies/glfw3"

project "SoulFireEngine"
	location "SoulFireEngine"
	kind "SharedLib"
	language "C++"

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
		"%{IncludeDirTable.GLFW}"
	}

	links {
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"SF_PLATFORM_WINDOWS",
			"SF_BUILDING_DLL"
		}

	filter "configurations:Debug"
		defines "SF_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "SF_RELEASE"
		optimize "On"

	filter "configurations:Distribution"
		defines "SF_DISTRIBUTION"
		optimize "On"



project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"SoulFireEngine/src"
	}

	links
	{
		"SoulFireEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"SF_PLATFORM_WINDOWS"
		}

		postbuildcommands
		{
			("{COPY} ../bin/" ..outputdir.. "/SoulFireEngine/SoulFireEngine.dll ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "SF_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "SF_RELEASE"
		optimize "On"

	filter "configurations:Distribution"
		defines "SF_DISTRIBUTION"
		optimize "On"