project "GeometryLibTest"

kind "ConsoleApp"
targetdir "../_tests"

includedirs{
	"../GeometryLib/include",
	"../UtilsLibSpecific/include",
}

links {
	"GeometryLib",
	"UtilsLibSpecific",
}

files {
	"**.cpp",
	"**.h"
}

configuration "Release"
	flags{ "Unicode" }

configuration "Debug"
	flags{ "Unicode" }
