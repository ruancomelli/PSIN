project "PropertyLibTest"

kind "ConsoleApp"
targetdir "../_tests"

includedirs{
	"../PropertyLib/include"
}

links {
	"PropertyLib"
}

files {
	"**.cpp",
	"**.h"
}

configuration "Release"
	flags{ "Unicode" }

configuration "Debug"
	flags{ "Unicode" }
