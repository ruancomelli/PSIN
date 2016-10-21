project "ForceModelLibTest"

kind "ConsoleApp"
targetdir "../_tests"

includedirs{
	"../UtilsLibSpecific/include",
	"../EntityLib/include",
	"../ForceModelLib/include"
}

links {
	"UtilsLibSpecific",
	"EntityLib",
	"ForceModelLib"
}

files {
	"**.cpp",
	"**.h"
}

configuration "Release"
	flags{ "Unicode" }

configuration "Debug"
	flags{ "Unicode" }
