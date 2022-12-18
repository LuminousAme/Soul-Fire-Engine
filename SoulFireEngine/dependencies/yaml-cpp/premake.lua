project "yaml-cpp"
    kind "StaticLib"
    language "C++"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

    files
    {
       "src/**.h",
	   "src/**.cpp",
	   "include/**.h"
    }

	includedirs
	{
		"include"
	}

	filter "system:windows"
        systemversion "latest"
		cppdialect "C++17"
		staticruntime "On"

	filter "configurations:Debug"
		defines "SF_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "SF_RELEASE"
		runtime "Release"
		optimize "On"