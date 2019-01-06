workspace "windows-timescale-hook"
	location "./build"
	objdir "%{wks.location}/obj"
	targetdir "%{wks.location}/bin/%{cfg.architecture}/%{cfg.buildcfg}"
	buildlog "%{wks.location}/obj/%{cfg.architecture}/%{cfg.buildcfg}/%{prj.name}/%{prj.name}.log"
	configurations { "Debug", "Release" }
	platforms { "x86", "x64" }
	
	buildoptions { "/std:c++latest", "/utf-8", "/Zm200" }
	systemversion "10.0.17763.0"

	flags { "NoIncrementalLink", "NoEditAndContinue", "NoMinimalRebuild", "MultiProcessorCompile"}

	configuration "windows"
		defines { "_WINDOWS", "WIN32" }

	configuration "Release*"
		defines { "NDEBUG" }
		optimize "On"

	configuration "Debug*"
		defines { "DEBUG", "_DEBUG" }
		optimize "Debug"
		if symbols ~= nil then
			symbols "On"
		else
			flags { "Symbols" }
		end
		
	project "windows-timescale-hook"
		kind "SharedLib"
		language "C++"
		files {
			"./src/**.hpp",
			"./src/**.cpp",
		}
		includedirs {
			"%{prj.location}/src",
			"./src",
		}
		resincludedirs {
			"$(ProjectDir)src"
		}

		pchheader "pch.hpp"
		pchsource "src/pch.cpp"

		vpaths
		{
			["*"] = { "./src/**" },
		}

		flags { "UndefinedIdentifiers" }
		warnings "Extra"

		if symbols ~= nil then
			symbols "On"
		else
			flags { "Symbols" }
		end

		configuration "Release*"
			flags {
				"FatalCompileWarnings",
				"FatalLinkWarnings",
			}
		configuration {}