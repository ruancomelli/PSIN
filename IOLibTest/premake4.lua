project "IOLibTest"

kind "ConsoleApp"
targetdir "../_tests"

includedirs{
	"../IOLib/include",
	"../UtilsLibSpecific/include",
	"../EntityLib/include",
	"../ForceModelLib/include",
	"../SimulationLib/include"
}

links {
	"IOLib",
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
