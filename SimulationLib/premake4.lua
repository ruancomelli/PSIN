project "SimulationLib"

kind "StaticLib"
targetdir "../_lib"

includedirs {
	"./include",
	"../UtilsLibSpecific/include",
	"../EntityLib/include",
	"../ForceModelLib/include"
}

links{
	"UtilsLibSpecific",
	"EntityLib",
	"ForceModelLib"
}

files {
	"**.cpp",
	"**.h"
}
