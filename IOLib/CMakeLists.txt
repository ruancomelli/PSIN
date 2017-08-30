project(IOLib)

set(Dependencies UtilsLib PropertyLib EntityLib InteractionLib)

#INCLUDE DIRECTORIES
foreach(Dependency ${Dependencies})
	include_directories (${CMAKE_SOURCE_DIR}/${Dependency}/include)
endforeach()
include_directories(${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/include)

#SEARCH FOR .CPP AND .H FILES
file(GLOB_RECURSE ${PROJECT_NAME}_headers ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/include/*.hpp)
file(GLOB_RECURSE ${PROJECT_NAME}_headers ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/include/*.tpp)
file(GLOB_RECURSE ${PROJECT_NAME}_sources ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/source/*.cpp)

#ADD LIBRARY
add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers})

#LINK LIBRARIES
foreach (Dependency ${Dependencies})
	target_link_libraries (${PROJECT_NAME} ${Dependency})
endforeach ()

#DEFINE OUTPUT LOCATION
install(
	TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION libs
	ARCHIVE DESTINATION archives
)
