#Felipe Giacomelli - UFSC, SINMEC - October, 2016 - felipe.g@sinmec.ufsc.br
#
#

project(EntityLibTest)

#INCLUDE DIRECTORIES
include_directories(${CMAKE_SOURCE_DIR}/UtilsLibSpecific/include)
include_directories(${CMAKE_SOURCE_DIR}/EntityLib/include)

#LINK DIRECTORIES
link_directories(${CMAKE_SOURCE_DIR}/UtilsLibSpecific/source)
link_directories(${CMAKE_SOURCE_DIR}/EntityLib/source)

#SEARCH FOR .CPP FILES
file(GLOB ${PROJECT_NAME}_sources ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/*.cpp)

#ADD EXECUTABLE
add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_sources})

#LINK LIBRARIES
target_link_libraries(UtilsLibSpecific)
target_link_libraries(EntityLib)

#DEFINE OUTPUT LOCATION
install(
	TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION	apps
	ARCHIVE DESTINATION archives
)
