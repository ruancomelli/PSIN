solution "ParticleSimulator"

configurations {"Release", "Debug"}
configuration {"Release"}
	flags {"StaticRuntime","Symbols", "NoMinimalRebuild", "OptimizeSpeed"}
configuration {"Debug"}
	flags {"StaticRuntime","Symbols", "NoMinimalRebuild", "NoEditAndContinue"}

platforms {"x32", "x64"}

configuration {"Debug", "x32"}
	targetsuffix "_d"

configuration {"Release", "x64"}
	targetsuffix "_x64"

configuration {"Debug", "x64"}
	targetsuffix "_d_x64"

configuration {"windows", "Debug"}
	defines {"WIN32", "_DEBUG", "_CONSOLE", "_CRT_SECURE_NO_WARNINGS"}
	linkoptions { "/ignore:4006,4221" }

configuration {"windows", "Release"}
	defines {"WIN32", "NDEBUG", "_CONSOLE", "_CRT_SECURE_NO_WARNINGS"}
	linkoptions { "/ignore:4006,4221" }

configuration {}

language "C++"

location ("../_build")

includedirs {
	"../../external_content/boost-1.55/windows/include/",
}

configuration "x32"

libdirs {
	"../../external_content/boost-1.55/windows/lib/x32",
}

links{
}

configuration "x64"

libdirs {
	"../../external_content/boost-1.55/windows/lib/x64",
}


links{
}

configuration {"x32","Debug"}

includedirs {
}

libdirs {
}

links{
}

configuration {"x32","Release"}

includedirs {
}

libdirs {
}

links{
}

configuration {"x64","Debug"}

includedirs {
}

libdirs {
}

links{
}

configuration {"x64","Release"}

includedirs {
}

libdirs {
}

links{
}

configuration {"x64"}

links{
}


configuration {}

--include "../EFVLibTest"
include "../UtilsLibSpecificTest"
include "../SimulationTest"
include "../ForceModelLibTest"
include "../CollidingSpheres"
include "../CollidingParticles"

--include "../EFVLib"
include "../UtilsLibSpecific"
include "../EntityLib"
include "../ForceModelLib"
include "../IOLib"
include "../SimulationLib"