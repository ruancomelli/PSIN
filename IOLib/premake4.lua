project "IOLib"

kind "StaticLib"
targetdir "../_lib"

includedirs {
	"./include",
	"../UtilsLibSpecific/include",
	"../EntityLib/include",
	"../ForceModelLib/include",
	"../SimulationLib/include",
}

links{
	"UtilsLibSpecific",
	"EntityLib",
	"ForceModelLib",
	"SimulationLib",
}

files {
	"**.cpp",
	"**.h"
}
