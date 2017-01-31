#Felipe Giacomelli - UFSC, SINMEC - November, 2016 - felipe.g@sinmec.ufsc.br
#
#

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

if(UNIX)
	#SET THE DESIRED COMPILER
	set(CMAKE_C_COMPILER "/usr/bin/gcc")
	set(CMAKE_CXX_COMPILER "/usr/bin/g++")
	
	#SET DEBUG COMPILATION FLAGS
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra")

	#SET RELEASE COMPILATION FLAGS
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
else()
	#SET THE DESIRED COMPILER
	set(CMAKE_C_COMPILER "C:/Program File (x86)/Microsoft Visual Studio 14.0/VC/bin/x86_amd64/cl")
	set(CMAKE_CXX_COMPILER "C:/Program File (x86)/Microsoft Visual Studio 14.0/VC/bin/x86_amd64/cl")

	#SET DEBUG COMPILATION FLAGS
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /W4")

	#SET RELEASE COMPILATION FLAGS
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /02")
endif()

message("\n\nC++ compiler: ${CMAKE_CXX_COMPILER}")
message("Debug flags: ${CMAKE_CXX_FLAGS_DEBUG}")
message("Release flags: ${CMAKE_CXX_FLAGS_RELEASE}\n\n")Nã

#ABOUT THE PROJECT
project(ParticleSimulator)
set(VERSION_MAJOR "6")
set(VERSION_MINOR "0")
set(VERSION_PATCH "0")
set(VERSION "${VERSION_MAJOR}.${VERSION_MAJOR}.{VERSION_PATCH}")

#SET WHERE THE FILES WILL BE CREATED
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/archives)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/apps) 

#EXTERNAL CONTENT


#ADD SUBDIRECTORIES
add_subdirectory(UtilitiesLib)
add_subdirectory(UtilitiesLibTest)
add_subdirectory(LinearSystemLib)
add_subdirectory(LinearSystemTest)
add_subdirectory(InterpolatorLib)
add_subdirectory(InterpolatorTest)
add_subdirectory(MainApp)