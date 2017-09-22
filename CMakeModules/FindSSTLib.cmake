# Find the glorious and almighty SSTLib
#
# SSTLIB_DIR must be set at ~/.bashrc
# SSTLIB_ARCH must be set at ~/.bashrc
# SSTLIB_DIR must be added to PATH at ~/.bash_profile
# The SSTLibConfig.cmake file is by default at <SSTLIB_DIR/SSTLIB_ARCH>.
#
# SSTLIB_FOUND       		- 
# SSTLIB_INCLUDE_DIR 		- 
# SSTLIB_LIBRARIES 			-

include (${SSTLIB_DIR}/${SSTLIB_ARCH}/SSTLibConfig.cmake)
find_path (SSTLIB_INCLUDE_DIR Algebra/Algorithms.h ${SSTLIB_DIR}/${SSTLIB_ARCH}/include)
find_library (SSTLIB_LIBRARY Algebra.a ${SSTLIB_DIR}/${SSTLIB_ARCH}/static_libs)
set (SSTLIB_COMPONENTS ACM Algebra MatrixOutliner PetscInterface  Simulator  SolverMask  VariableComputer)

set (SSTLIB_FOUND FALSE)
if (SSTLIB_INCLUDE_DIR)
	if (SSTLIB_LIBRARY)
		set (SSTLIB_FOUND TRUE)
		set (SSTLIB_INCLUDE_DIR ${SSTLIB_INCLUDE_DIR})
		set (SSTLIB_LIBRARIES ${SSTLIB_COMPONENTS})
	endif ()
endif ()

if (SSTLIB_FOUND)
	message ("-- Found SSTLib: ${SSTLIB_DIR}/${SSTLIB_ARCH}")
else ()
	message ("\n\n-- Could not find SSTLib.\n\n")
endif ()

# Debug this script - useful information
#message ("\n-- SSTLIB_FOUND: ${SSTLIB_FOUND}")
#message ("\n-- SSTLIB_INCLUDE_DIR: ${SSTLIB_INCLUDE_DIR}")
#message ("\n-- SSTLIB_LIBRARIES: ${SSTLIB_LIBRARIES}")
