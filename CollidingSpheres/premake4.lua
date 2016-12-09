project "CollidingSpheres"

kind "ConsoleApp"
targetdir "../_tests"

includedirs{
	"./include",
	"../IOLib/include",
	"../EntityLib/include",
	"../UtilsLibSpecific/include",
	"../ForceModelLib/include",
}

links {
	"IOLib",
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