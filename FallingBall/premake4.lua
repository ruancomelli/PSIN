project "FallingBall"

kind "ConsoleApp"
targetdir "../_tests"

includedirs{
	"../EntityLib/include",
	"../UtilsLibSpecific/include",
	"../ForceModelLib/include",
}

links {
	"EntityLib",
	"UtilsLibSpecific",
	"ForceModelLib",
}

files {
	"**.cpp",
	"**.h"
}

configuration "Release"
	flags{ "Unicode" }

configuration "Debug"
	flags{ "Unicode" }