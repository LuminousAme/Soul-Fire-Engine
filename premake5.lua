-- p

workspace "Soul Fire"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

outputdir = "%{cfg.buildcgf}-%{cfg.system}-%{cfg.architecture}"

project "SoulFireEngine"
	location "SoulFireEngine"
	kind "SharedLib"
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
		"%{prj.name}/dependencies/spdlog/include"
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

		postbuildcommands
		{
			("{Copy} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
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

	filter "configurations:Debug"
		defines "SF_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "SF_RELEASE"
		optimize "On"

	filter "configurations:Distribution"
		defines "SF_DISTRIBUTION"
		optimize "On"