# Find the glorious and almighty EFVLib
#
# EFVLIB_DIR must be set at ~/.bashrc
# EFVLIB_ARCH must be set at ~/.bashrc
# EFVLIB_DIR must be added to PATH at ~/.bash_profile
# The EFVLibConfig.cmake file is by default at <EFVLIB_DIR/EFVLIB_ARCH>.
#
# EFVLIB_FOUND       		- 
# EFVLIB_INCLUDE_DIR 		- 
# EFVLIB_LIBRARIES 			-

include (${EFVLIB_DIR}/${EFVLIB_ARCH}/EFVLibConfig.cmake)
find_path (EFVLIB_INCLUDE_DIR Utils/Array3D.h ${EFVLIB_DIR}/${EFVLIB_ARCH}/include)
find_library (EFVLIB_LIBRARY Utils.a ${EFVLIB_DIR}/${EFVLIB_ARCH}/static_libs)
set (EFVLIB_COMPONENTS BoundaryCondition Fields Grid IO MuParser NumericalAnalysis Operators ParallelToolkit ScriptSystem Utils)

set (EFVLIB_FOUND FALSE)
if (EFVLIB_INCLUDE_DIR)
	if (EFVLIB_LIBRARY)
		set (EFVLIB_FOUND TRUE)
		set (EFVLIB_INCLUDE_DIR ${EFVLIB_INCLUDE_DIR})
		set (EFVLIB_LIBRARIES ${EFVLIB_COMPONENTS})
	endif ()
endif ()

if (EFVLIB_FOUND)
	message ("-- Found EFVLib: ${EFVLIB_DIR}/${EFVLIB_ARCH}")
else ()
	message ("\n\n-- Could not find EFVLib.\n\n")
endif ()

# Debug this script - useful information
#message ("\n-- EFVLIB_FOUND: ${EFVLIB_FOUND}")
#message ("\n-- EFVLIB_INCLUDE_DIR: ${EFVLIB_INCLUDE_DIR}")
#message ("\n-- EFVLIB_LIBRARIES: ${EFVLIB_LIBRARIES}")
