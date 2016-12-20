project "GeometryLib"

kind "StaticLib"
targetdir "../_lib"

includedirs {
	"./include",
	"../UtilsLibSpecific/include",
}

links{
	"UtilsLibSpecific",
}

files {
	"**.cpp",
	"**.h"
}
