#Felipe Giacomelli - UFSC, SINMEC - November, 2016 - felipe.g@sinmec.ufsc.br
#
#

CMAKE_MINIMUM_REQUIRED(VERSION 3.6)

if(UNIX)
	#SET THE DESIRED COMPILER
	set(CMAKE_C_COMPILER "/usr/bin/gcc")
	set(CMAKE_CXX_COMPILER "/usr/bin/g++")
	
	#SET DEBUG COMPILATION FLAGS
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pedantic -Wall -Wextra")

	#SET RELEASE COMPILATION FLAGS
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -pedantic -O2")
	
	#SET BUILD TYPE
	if(CMAKE_BUILD_TYPE MATCHES DEBUG)
		set(CMAKE_BUILD_DIR	"Debug")
	elseif(CMAKE_BUILD_TYPE MATCHES RELEASE)
		set(CMAKE_BUILD_DIR	"Release")
	else()
		set(CMAKE_BUILD_TYPE "RELEASE")
		set(CMAKE_BUILD_DIR	"Release")
	endif()
	message("-- Build type: ${CMAKE_BUILD_TYPE}")
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_BUILD_DIR})
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${CMAKE_BUILD_DIR})
endif()


#ABOUT THE PROJECT
project(ParticleSimulator)
set(VERSION_MAJOR "1")
set(VERSION_MINOR "0")
set(VERSION_PATCH "0")
set(VERSION "${VERSION_MAJOR}.${VERSION_MAJOR}.${VERSION_PATCH}")

#SET WHERE THE FILES WILL BE CREATED
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/archives)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/apps)

#PRINT SOME MESSAGES
message("\n-- Project: ${PROJECT_NAME} ${VERSION}")
message("-- C++ compiler: ${CMAKE_CXX_COMPILER}")
message("-- Debug flags: ${CMAKE_CXX_FLAGS_DEBUG}")
message("-- Release flags: ${CMAKE_CXX_FLAGS_RELEASE}\n")

# BOOST
set(BOOST_PATH CACHE PATH "Path to Boost folder")
include_directories(${BOOST_PATH})

#ADD SUBDIRECTORIES
add_subdirectory(UtilsLibSpecific)
add_subdirectory(UtilsLibSpecificTest)
add_subdirectory(EntityLib)
add_subdirectory(EntityLibTest)
add_subdirectory(ForceModelLib)
add_subdirectory(ForceModelLibTest)
###add_subdirectory(IOLib)
###add_subdirectory(CollidingSpheres)
