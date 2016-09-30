project "FallingBall"

kind "ConsoleApp"
targetdir "../_tests"

includedirs{
	"../UtilsLibSpecific/include",
}

links {
	"UtilsLibSpecific"
}

files {
	"**.cpp",
	"**.h"
}

configuration "Release"
	flags{ "Unicode" }
configuration "Debug"
	flags{ "Unicode" }

