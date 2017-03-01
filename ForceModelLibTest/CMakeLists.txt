#Felipe Giacomelli - UFSC, SINMEC - October, 2016 - felipe.g@sinmec.ufsc.br
#
#

project(ForceModelLibTest)

#INCLUDE DIRECTORIES
include_directories(${CMAKE_SOURCE_DIR}/UtilsLib/include)
include_directories(${CMAKE_SOURCE_DIR}/EntityLib/include)
include_directories(${CMAKE_SOURCE_DIR}/ForceModelLib/include)
include_directories(${CMAKE_SOURCE_DIR}/PropertyLib/include)
include_directories(${CMAKE_SOURCE_DIR}/IOLib/include)

#LINK DIRECTORIES
link_directories(${CMAKE_SOURCE_DIR}/UtilsLib/source)
link_directories(${CMAKE_SOURCE_DIR}/EntityLib/source)
link_directories(${CMAKE_SOURCE_DIR}/ForceModelLib/source)
link_directories(${CMAKE_SOURCE_DIR}/PropertyLib/source)
link_directories(${CMAKE_SOURCE_DIR}/IOLib/source)

#SEARCH FOR .CPP FILES
file(GLOB ${PROJECT_NAME}_sources ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/*.cpp)

#ADD EXECUTABLE
add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_sources})

#LINK LIBRARIES
target_link_libraries(${PROJECT_NAME} UtilsLib)
target_link_libraries(${PROJECT_NAME} EntityLib)
target_link_libraries(${PROJECT_NAME} ForceModelLib)
target_link_libraries(${PROJECT_NAME} PropertyLib)
target_link_libraries(${PROJECT_NAME} IOLib)

#DEFINE OUTPUT LOCATION
install(
	TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION	apps
	ARCHIVE DESTINATION archives
)
