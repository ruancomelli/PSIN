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
	--linkoptions { "/ignore:4006,4221" }

configuration {"windows", "Release"}
	defines {"WIN32", "NDEBUG", "_CONSOLE", "_CRT_SECURE_NO_WARNINGS"}
	--inkoptions { "/ignore:4006,4221" }

configuration {}

language "C++"

location ("../_build")

includedirs {
	"../external_content/boost_1_55_0/windows/include/",
}

links {
	--"boost_unit_test_framework",
}

configuration "x32"

libdirs {
	"../externalContent/boost_1_55_0/iwindowsLib/x32",
}

links{
	--"cgns",
}

configuration "x64"

libdirs {
	"../externalContent/boost_1_55_0/iwindowsLib/x64",
}


links{
	--"cgns",
}

configuration {"x32","Debug"}

includedirs {
	--"../../external_content/HDF5-1.8.12/include",
	--"../../external_content/petsc-3.3-p6/linux/include/debug",
}

libdirs {
	--"../../external_content/HDF5-1.8.12/lib/x32/debug",
	--"../../external_content/petsc-3.3-p6/linux/lib/x32/debug",
}

links{
	--"hdf5d",
	--"hdf5_cppd",
}

configuration {"x32","Release"}

includedirs {
	--"../../external_content/HDF5-1.8.12/include",
	--"../../external_content/petsc-3.3-p6/linux/include/release",
}

libdirs {
	--"../../external_content/HDF5-1.8.12/lib/x32/release",
	--"../../external_content/petsc-3.3-p6/linux/lib/x32/release",
}

links{
	--"hdf5",
	--"hdf5_cpp",
}

configuration {"x64","Debug"}

includedirs {
	--"../../external_content/HDF5-1.8.12/include",
	--"../../external_content/petsc-3.3-p6/linux/include/debug",
}

libdirs {
	--"../../external_content/boost-1.55/linux/lib/x64/debug",
	--"../../external_content/HDF5-1.8.12/lib/x64/debug",
	--"../../external_content/petsc-3.3-p6/linux/lib/x64/debug",
	--"../../external_content/metis-5.1.0/linux/lib/x64/debug",
}

links{
	--"hdf5d",
	--"hdf5_cppd",
}

configuration {"x64","Release"}

includedirs {
	--"../../external_content/HDF5-1.8.12/include",
	--"../../external_content/petsc-3.3-p6/linux/include/release",
}

libdirs {
	--"../../external_content/boost-1.55/linux/lib/x64/release",
	--"../../external_content/HDF5-1.8.12/lib/x64/release",
	--"../../external_content/petsc-3.3-p6/linux/lib/x64/release",
	--"../../external_content/metis-5.1.0/linux/lib/x64/release",
}

links{
	--"hdf5",
	--"hdf5_cpp",
}


configuration {}

--include "../EFVLibTest"
include "../CollidingSpheres"
include "../CollidingParticles"
include "../FallingBall"
include "../SimulationTest"
include "../UtilsLibSpecificTest"

--include "../EFVLib"
include "../EntityLib"
include "../ForceModelLib"
include "../UtilsLibSpecific"
include "../SimulationLib"
include "../IOLib"