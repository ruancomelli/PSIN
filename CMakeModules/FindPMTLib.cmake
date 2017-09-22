# Find the glorious and almighty PMTLib
#
# PMTLIB_DIR must be set at ~/.bashrc
# PMTLIB_ARCH must be set at ~/.bashrc
# PMTLIB_DIR must be added to PATH at ~/.bash_profile
# The PMTLibConfig.cmake file is by default at <PMTLIB_DIR/PMTLIB_ARCH>.
#
# PMTLIB_FOUND       		- 
# PMTLIB_INCLUDE_DIR 		- 
# PMTLIB_LIBRARIES 			-

include (${PMTLIB_DIR}/${PMTLIB_ARCH}/PMTLibConfig.cmake)
find_path (PMTLIB_INCLUDE_DIR DarcyFlow/CompressiveAccumulationAdder.h ${PMTLIB_DIR}/${PMTLIB_ARCH}/include)
find_library (PMTLIB_LIBRARY DarcyFlow.a ${PMTLIB_DIR}/${PMTLIB_ARCH}/static_libs)
set (PMTLIB_COMPONENTS DarcyFlow Geomechanics Structural)

set (PMTLIB_FOUND FALSE)
if (PMTLIB_INCLUDE_DIR)
	if (PMTLIB_LIBRARY)
		set (PMTLIB_FOUND TRUE)
		set (PMTLIB_INCLUDE_DIR ${PMTLIB_INCLUDE_DIR})
		set (PMTLIB_LIBRARIES ${PMTLIB_COMPONENTS})
	endif ()
endif ()

if (PMTLIB_FOUND)
	message ("-- Found PMTLib: ${PMTLIB_DIR}/${PMTLIB_ARCH}")
else ()
	message ("\n\n-- Could not find PMTLib.\n\n")
endif ()

# Debug this script - useful information
#message ("\n-- PMTLIB_FOUND: ${PMTLIB_FOUND}")
#message ("\n-- PMTLIB_INCLUDE_DIR: ${PMTLIB_INCLUDE_DIR}")
#message ("\n-- PMTLIB_LIBRARIES: ${PMTLIB_LIBRARIES}")
