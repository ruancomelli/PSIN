CMAKE_MINIMUM_REQUIRED(VERSION 3.6)

set (CMAKE_CXX_STANDARD 14)

if(UNIX)
	#SET THE DESIRED COMPILER
	set(CMAKE_C_COMPILER "/usr/bin/gcc")
	set(CMAKE_CXX_COMPILER "/usr/bin/g++")

	#SET DEBUG COMPILATION FLAGS
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic")

	#SET RELEASE COMPILATION FLAGS
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -pedantic -O2")

	if(DEFINED CMAKE_BUILD_TYPE)
		set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of
		build, options are: Debug Release.")
	else()
		set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of
		build, options are: Debug Release.")
	endif()

	#SET WHERE THE FILES WILL BE CREATED
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/archives/${CMAKE_BUILD_TYPE})
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs/${CMAKE_BUILD_TYPE})
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/apps/${CMAKE_BUILD_TYPE})

elseif(WIN32)
	#SET DEBUG COMPILATION FLAGS
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Za")

	#SET RELEASE COMPILATION FLAGS
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Za")

	#SET WHERE THE FILES WILL BE CREATED
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/archives/${CMAKE_BUILD_TYPE})
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs/${CMAKE_BUILD_TYPE})
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/apps/${CMAKE_BUILD_TYPE})

endif()

#ABOUT THE PROJECT
project(ParticleSimulator)
set(VERSION_MAJOR "1")
set(VERSION_MINOR "0")
set(VERSION_PATCH "0")
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

# USER MODULES LOCATION
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake_modules")

# BOOST
if(UNIX)
	set(BOOST_ROOT $ENV{BOOST_DIR}/${CMAKE_BUILD_TYPE})
	
	# FIND BOOST
	set (Components_Boost filesystem program_options system test_exec_monitor unit_test_framework)
	set (Boost_USE_STATIC_LIBS ON)
	set (Boost_USE_STATIC_RUNTIME ON)
	set (Boost_USE_MULTITHREADED ON)
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
elseif(WIN32)
	get_filename_component(GIT_PROJECTS_DIR "${CMAKE_BINARY_DIR}/../.." ABSOLUTE)

	if(EXISTS ${GIT_PROJECTS_DIR}/boost_1_63_0_compiled/)
		set(BOOST_INCLUDE_DIR ${GIT_PROJECTS_DIR}/boost_1_63_0_compiled/)
		set(BOOST_LIBRARY_DIR ${GIT_PROJECTS_DIR}/boost_1_63_0_compiled/lib)
	endif()

	include_directories(${BOOST_INCLUDE_DIR})
	link_directories(${BOOST_LIBRARY_DIR})
endif()

#PRINT SOME MESSAGES
message("\n-- Project: ${PROJECT_NAME} ${VERSION}")
message("-- C++ compiler: ${CMAKE_CXX_COMPILER}")
message("-- Debug flags: ${CMAKE_CXX_FLAGS_DEBUG}")
message("-- Release flags: ${CMAKE_CXX_FLAGS_RELEASE}")
message("-- Cmake build type: ${CMAKE_BUILD_TYPE}")

# ROOT PATH TO USE IN PROGRAMS
add_definitions(-DPROJECT_PATH="${CMAKE_SOURCE_DIR}/")
message("\nThe 'PROJECT_PATH' is ${CMAKE_SOURCE_DIR}/")
message("Do not try to use the output files outside the project")
message("(do not copy and paste somewhere else).")
message("Possible errors in programs (executables) and in python (process data)\n")

#ADD SUBDIRECTORIES
# add_subdirectory(MuParserLib)
add_subdirectory(UtilsLib)
add_subdirectory(UtilsLibTest)
add_subdirectory(EntityLib)
add_subdirectory(EntityLibTest)
add_subdirectory(InteractionLib)
add_subdirectory(InteractionLibTest)
add_subdirectory(IOLib)
add_subdirectory(IOLibTest)
add_subdirectory(PropertyLib)
add_subdirectory(PropertyLibTest)
add_subdirectory(CollidingSpheres)
# add_subdirectory(ScriptSystemLib)
# add_subdirectory(ScriptSystemLibTest)
add_subdirectory(SimulationLib)
add_subdirectory(SimulationLibTest)
