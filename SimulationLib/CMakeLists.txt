project(SimulationLib)

#INCLUDE DIRECTORIES
include_directories(${CMAKE_SOURCE_DIR}/EntityLib/include)
include_directories(${CMAKE_SOURCE_DIR}/InteractionLib/include)
include_directories(${CMAKE_SOURCE_DIR}/IOLib/include)
include_directories(${CMAKE_SOURCE_DIR}/PropertyLib/include)
include_directories(${CMAKE_SOURCE_DIR}/UtilsLib/include)
include_directories(${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/include)

#LINK DIRECTORIES
link_directories(${CMAKE_SOURCE_DIR}/EntityLib/source)
link_directories(${CMAKE_SOURCE_DIR}/InteractionLib/source)
link_directories(${CMAKE_SOURCE_DIR}/IOLib/source)
link_directories(${CMAKE_SOURCE_DIR}/PropertyLib/source)
link_directories(${CMAKE_SOURCE_DIR}/UtilsLib/source)

#SEARCH FOR .CPP AND .H FILES
file(GLOB ${PROJECT_NAME}_headers ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/include/*.hpp)
file(GLOB ${PROJECT_NAME}_sources ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/source/*.cpp)

#ADD LIBRARY
add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers})

#LINK LIBRARIES
target_link_libraries(${PROJECT_NAME} EntityLib)
target_link_libraries(${PROJECT_NAME} InteractionLib)
target_link_libraries(${PROJECT_NAME} IOLib)
target_link_libraries(${PROJECT_NAME} PropertyLib)
target_link_libraries(${PROJECT_NAME} UtilsLib)

#DEFINE OUTPUT LOCATION
install(
	TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION libs
	ARCHIVE DESTINATION archives
)
