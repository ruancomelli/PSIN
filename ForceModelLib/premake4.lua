project "ForceModel"

kind "StaticLib"
targetdir "../_lib"

includedirs {
	"./include",
	"../UtilsLibSpecific/include",
	"../EntityLib/include",
}

links {
	"UtilsLibSpecific",
	"EntityLib"
}

files {
	"**.cpp",
	"**.h"
}