project "spdlog"
    kind "StaticLib"
    language "C++"
    
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
	{
        "include/spdlog/**.h",
        "include/spdlog/**.cpp",
        "src/**.cpp",
        "src/**.h"
    }

    includedirs {
        "include"
    }

    disablewarnings {
        "26812"
    }

    warnings "off"

    defines {
        "SPDLOG_COMPILED_LIB"
    }
    
	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"