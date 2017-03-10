#Felipe Giacomelli - UFSC, SINMEC - November, 2016 - felipe.g@sinmec.ufsc.br
#
#

CMAKE_MINIMUM_REQUIRED(VERSION 3.6)

#SET WHERE THE FILES WILL BE CREATED
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/archives)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/apps)

if(UNIX)
	#SET THE DESIRED COMPILER
	set(CMAKE_C_COMPILER "/usr/bin/gcc")
	set(CMAKE_CXX_COMPILER "/usr/bin/g++")

	set (CMAKE_CXX_STANDARD 11)
	
	#SET DEBUG COMPILATION FLAGS
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic")

	#SET RELEASE COMPILATION FLAGS
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -pedantic -O2")
	
	#SET BUILD TYPE
	if(CMAKE_BUILD_TYPE MATCHES DEBUG)
		set(CMAKE_BUILD_DIR	"Debug")
	elseif(CMAKE_BUILD_TYPE MATCHES RELEASE)
		set(CMAKE_BUILD_DIR	"Release")
	else()
		set(CMAKE_BUILD_TYPE "RELEASE")
		set(CMAKE_BUILD_DIR	"Release")
	endif()
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_BUILD_DIR})
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${CMAKE_BUILD_DIR})
endif ()

#SET BUILD TYPE
if(CMAKE_BUILD_TYPE MATCHES DEBUG)
	set(CMAKE_BUILD_DIR	"Debug")
elseif(CMAKE_BUILD_TYPE MATCHES RELEASE)
	set(CMAKE_BUILD_DIR	"Release")
else()
	set(CMAKE_BUILD_TYPE "RELEASE")
	set(CMAKE_BUILD_DIR	"Release")
endif()
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_BUILD_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${CMAKE_BUILD_DIR})


#ABOUT THE PROJECT
project(ParticleSimulator)
set(VERSION_MAJOR "1")
set(VERSION_MINOR "0")
set(VERSION_PATCH "0")
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

# BOOST
if(UNIX)
	set(BOOST_ROOT $ENV{BOOST_DIR})
elseif(WIN32)
	set (Boost_USE_STATIC_LIBS ON)
	set (Boost_USE_MULTITHREADED ON)
	get_filename_component(GIT_PROJECTS_DIR "${CMAKE_BINARY_DIR}/../.." ABSOLUTE)
	if(EXISTS ${GIT_PROJECTS_DIR}/boost_1_63_0)
		set(BOOST_ROOT ${GIT_PROJECTS_DIR}/boost_1_63_0)
	else()
		set(BOOST_ROOT CACHE PATH "Boost installation dir")
	endif()
endif()

set (Components_Boost filesystem test_exec_monitor unit_test_framework)
find_package (Boost COMPONENTS ${Components_Boost} REQUIRED)
if(Boost_FOUND)
	include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
endif()

# MACROS
# auto links with external libraries
macro (add_executable _target)
    _add_executable (${_target} ${ARGN})
    target_link_libraries (${_target} ${Boost_LIBRARIES})
endmacro()

macro(add_library _target )
   	_add_library (${_target} ${ARGN})
   	target_link_libraries (${_target} ${Boost_LIBRARIES})
endmacro()

#PRINT SOME MESSAGES
message("\n-- Project: ${PROJECT_NAME} ${VERSION}")
message("-- C++ compiler: ${CMAKE_CXX_COMPILER}")
message("-- Debug flags: ${CMAKE_CXX_FLAGS_DEBUG}")
message("-- Release flags: ${CMAKE_CXX_FLAGS_RELEASE}")

# ROOT PATH TO USE IN PROGRAMS
add_definitions(-DPROJECT_PATH="${CMAKE_SOURCE_DIR}/")
message("\nThe 'PROJECT_PATH' is ${CMAKE_SOURCE_DIR}/")
message("Do not try to use the output files outside the project")
message("(do not copy and paste somewhere else).")
message("Possible errors in programs (executables) and in python (process data)\n")

#ADD SUBDIRECTORIES
add_subdirectory(UtilsLib)
add_subdirectory(UtilsLibTest)
add_subdirectory(EntityLib)
add_subdirectory(EntityLibTest)
add_subdirectory(ForceModelLib)
add_subdirectory(ForceModelLibTest)
add_subdirectory(IOLib)
add_subdirectory(IOLibTest)
add_subdirectory(PropertyLib)
add_subdirectory(PropertyLibTest)
add_subdirectory(CollidingSpheres)
add_subdirectory(SimulationLib)
add_subdirectory(SimulationLibTest)
