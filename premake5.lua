workspace "Fountainhead"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buidcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Fountainhead/vendor/GLFW/include"
IncludeDir["Glad"] = "Fountainhead/vendor/Glad/include"
IncludeDir["ImGui"] = "Fountainhead/vendor/imgui"
IncludeDir["glm"] = "Fountainhead/vendor/glm"

include "Fountainhead/vendor/GLFW"
include "Fountainhead/vendor/Glad"
include "Fountainhead/vendor/imgui"


project "Fountainhead"
	location "Fountainhead"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "fhpch.h"
	pchsource "Fountainhead/src/fhpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"FH_PLATFORM_WINDOWS",
			"FH_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "FH_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "FH_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
		staticruntime "off"

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
		"Fountainhead/src",
		"Fountainhead/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Fountainhead"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"FH_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "FH_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "FH_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "DIST"
		runtime "Release"
		optimize "On"