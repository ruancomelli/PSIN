project "EntityLibTest"

kind "ConsoleApp"
targetdir "../_tests"

includedirs{
	"../UtilsLibSpecific/include",
	"../EntityLib/include",
}

links {
	"UtilsLibSpecific",
	"EntityLib",
}

files {
	"**.cpp",
	"**.h"
}

configuration "Release"
	flags{ "Unicode" }

configuration "Debug"
	flags{ "Unicode" }
