#Felipe Giacomelli - UFSC, SINMEC - October, 2016 - felipe.g@sinmec.ufsc.br
#
#

project(UtilsLibSpecificTest)

#INCLUDE DIRECTORIES
include_directories(${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/include)
include_directories(${CMAKE_SOURCE_DIR}/UtilsLibSpecific/include)

#LINK DIRECTORIES
link_directories(${CMAKE_SOURCE_DIR}/UtilsLibSpecific/source)

#SEARCH FOR .CPP FILES
file(GLOB ${PROJECT_NAME}_sources ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/*.cpp)

#ADD EXECUTABLE
add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_sources})

#LINK LIBRARIES
target_link_libraries(${PROJECT_NAME} UtilsLibSpecific)

#DEFINE OUTPUT LOCATION
install(
	TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION	apps
	ARCHIVE DESTINATION archives
)
