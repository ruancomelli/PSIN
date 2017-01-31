#Felipe Giacomelli - UFSC, SINMEC - October, 2016 - felipe.g@sinmec.ufsc.br
#
#

project(ForceModelLib)

#INCLUDE DIRECTORIES
include_directories(${CMAKE_SOURCE_DIR}/UtilsLibSpecific/include)
include_directories(${CMAKE_SOURCE_DIR}/EntityLib/include)
include_directories(${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/include)

#LINK THE DIRECTORIES
link_directories(${CMAKE_SOURCE_DIR}/UtilsLibSpecific/source)
link_directories(${CMAKE_SOURCE_DIR}/EntityLib/source)

#SEARCH FOR .CPP AND .H FILES
file(GLOB ${PROJECT_NAME}_headers ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/include/*.h)
file(GLOB ${PROJECT_NAME}_sources ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/source/*.cpp)

#ADD LIBRARY
add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers})

#LINK LIBRARIES
target_link_libraries(${PROJECT_NAME} UtilsLibSpecific)
target_link_libraries(${PROJECT_NAME} EntityLib)

#DEFINE OUTPUT LOCATION
install(
	TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION libs
	ARCHIVE DESTINATION archives
)
