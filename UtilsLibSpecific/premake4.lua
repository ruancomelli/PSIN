project "UtilsLibSpecific"

kind "StaticLib"
targetdir "../_lib"

includedirs {
	"./include"
}

links{
}

files {
	"**.cpp",
	"**.h"
}
