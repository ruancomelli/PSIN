project "EntityLib"

kind "StaticLib"
targetdir "../_lib"

includedirs {
	"./include",
	"../UtilsLibSpecific/include",
	"../IOLib/include"
}

links{
	"UtilsLibSpecific",
}

files {
	"**.cpp",
	"**.h"
}
