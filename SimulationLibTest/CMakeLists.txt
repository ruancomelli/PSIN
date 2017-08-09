project(SimulationLibTest)

#INCLUDE DIRECTORIES
include_directories(${CMAKE_SOURCE_DIR}/UtilsLib/include)
include_directories(${CMAKE_SOURCE_DIR}/EntityLib/include)
include_directories(${CMAKE_SOURCE_DIR}/InteractionLib/include)
include_directories(${CMAKE_SOURCE_DIR}/PropertyLib/include)
include_directories(${CMAKE_SOURCE_DIR}/IOLib/include)
include_directories(${CMAKE_SOURCE_DIR}/SimulationLib/include)

#LINK DIRECTORIES
link_directories(${CMAKE_SOURCE_DIR}/UtilsLib/source)
link_directories(${CMAKE_SOURCE_DIR}/EntityLib/source)
link_directories(${CMAKE_SOURCE_DIR}/InteractionLib/source)
link_directories(${CMAKE_SOURCE_DIR}/PropertyLib/source)
link_directories(${CMAKE_SOURCE_DIR}/IOLib/source)
link_directories(${CMAKE_SOURCE_DIR}/SimulationLib/source)

#SEARCH FOR .CPP FILES
file(GLOB_RECURSE${PROJECT_NAME}_sources ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/*.cpp)

#ADD EXECUTABLE
add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_sources})

#LINK LIBRARIES
target_link_libraries(${PROJECT_NAME} UtilsLib)
target_link_libraries(${PROJECT_NAME} EntityLib)
target_link_libraries(${PROJECT_NAME} InteractionLib)
target_link_libraries(${PROJECT_NAME} PropertyLib)
target_link_libraries(${PROJECT_NAME} IOLib)
target_link_libraries(${PROJECT_NAME} SimulationLib)

#DEFINE OUTPUT LOCATION
install(
	TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION	apps
	ARCHIVE DESTINATION archives
)
