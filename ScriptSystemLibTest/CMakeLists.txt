project(ScriptSystemLibTest)

set(Dependencies UtilsLib MuParserLib ScriptSystemLib)

foreach(Dependency ${Dependencies})
	include_directories (${CMAKE_SOURCE_DIR}/${Dependency}/include)
endforeach()

file (GLOB_RECURSE ${PROJECT_NAME}_sources ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/source/*.cpp)

add_executable (${PROJECT_NAME} ${${PROJECT_NAME}_sources})

foreach (Dependency ${Dependencies})
	target_link_libraries (${PROJECT_NAME} ${Dependency})
endforeach ()

#DEFINE OUTPUT LOCATION
install(
	TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION	apps
	ARCHIVE DESTINATION archives
)
