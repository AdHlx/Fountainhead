workspace "Fountainhead"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buidcfg}-%{cfg.system}-%{cfg.architecture}"

project "Fountainhead"
	location "Fountainhead"
	kind "SharedLib"
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "fhpch.h"
	pchsource "Fountainhead/src/fhpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"FH_PLATFORM_WINDOWS",
			"FH_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "FH_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "FH_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Fountainhead/vendor/spdlog/include",
		"Fountainhead/src"
	}

	links
	{
		"Fountainhead"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"FH_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "FH_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "FH_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "DIST"
		optimize "On"