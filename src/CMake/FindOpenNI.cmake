# Find OpenNI
#
# OPENNI_INCLUDE
# OPENNI_LIBRARY
# OPENNI_FOUND
#
# made by sycoso

FIND_PATH(OPENNI_NI_INCLUDE NAME XnOpenNI.h PATHS /usr/include/ni /usr/include/openni /usr/include/OpenNI /usr/local/include/ni /usr/local/include/openni /usr/local/include/OpenNI ~/.local/include/ni ~/.local/include/openni ~/.local/include/OpenNI)

FIND_PATH(NITE_INCLUDE NAME XnVNite.h PATHS /usr/include/nite /usr/include/NITE /usr/local/include/nite /usr/local/include/NITE ~/.local/include/nite ~/.local/include/NITE)

set(OPENNI_INCLUDE
	${OPENNI_NI_INCLUDE}
	${NITE_INCLUDE}
)

FIND_LIBRARY(OPENNI_NI_LIBRARY NAME OpenNI PATHS /usr/lib /usr/local/lib ~/.local/lib)
FIND_LIBRARY(NITE_LIBRARY NAME XnVCNITE_1_3_1 PATHS /usr/lib /usr/local/lib ~/.local/lib)

set(OPENNI_LIBRARY
	${OPENNI_NI_LIBRARY}
	${NITE_LIBRARY}
)

IF(OPENNI_INCLUDE AND OPENNI_LIBRARY)
	SET(OPENNI_FOUND TRUE)
ENDIF(OPENNI_INCLUDE AND OPENNI_LIBRARY)

IF (OPENNI_FOUND)
	IF (NOT OPENNI_FIND_QUIETLY)
		MESSAGE(STATUS "Found OpenNI: ${OPENNI_LIBRARY}")
	ENDIF (NOT OPENNI_FIND_QUIETLY)
ELSE (OPENNI_FOUND)
	IF (OPENNI_FIND_REQUIRED)
	        MESSAGE(FATAL_ERROR "Could not find OpenNI.")
	ENDIF (OPENNI_FIND_REQUIRED)
ENDIF (OPENNI_FOUND)
