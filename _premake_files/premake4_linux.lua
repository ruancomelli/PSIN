solution "ParticleSimulator"

configurations {"Release", "Debug"}
configuration {"Release"}
	flags {"StaticRuntime","Symbols", "NoMinimalRebuild", "OptimizeSpeed"}
configuration {"Debug"}
	flags {"StaticRuntime","Symbols", "NoMinimalRebuild", "NoEditAndContinue"}

platforms {"x64"}

configuration {"Release", "x64"}
	targetsuffix "_x64"

configuration {"Debug", "x64"}
	targetsuffix "_d_x64"

configuration {}

language "C++"

location ("../_build")

includedirs {
}

links{
}

configuration "x64"

libdirs {
	"../../external_content/boost-1.55/linux/lib/x64",
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


configuration {}

--include "../EFVLibTest"
include "../CollidingSpheres"
include "../GeometryLibTest"
include "../IOLibTest"
include "../EntityLibTest"
include "../UtilsLibSpecificTest"
include "../SimulationTest"
include "../ForceModelLibTest"
include "../CollidingParticles"

--include "../EFVLib"
include "../UtilsLibSpecific"
include "../GeometryLib"
include "../EntityLib"
include "../ForceModelLib"
include "../IOLib"
include "../SimulationLib"
