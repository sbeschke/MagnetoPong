cmake_minimum_required( VERSION 2.8 )
project(MagnetoPong)


# Set Build Type
if(CMAKE_BUILD_TYPE STREQUAL "")
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

if(CMAKE_C_COMPILER MATCHES "gcc")
	set(ENABLE_ALL_WARNINGS OFF CACHE BOOL "Choose whether to enable all warnings or not")
endif()


###############
# Set Defines #
###############

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "DEBUG" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo" OR CMAKE_BUILD_TYPE STREQUAL "RELWITHDEBINFO")
	add_definitions(-pg)
endif()

set(CMAKE_EXE_LINKER_FLAGS_DEBUG
	${CMAKE_EXE_LINKER_FLAGS_DEBUG}
	-pg
)

set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO
	${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO}
	-pg
)

if(ENABLE_ALL_WARNINGS)
	add_definitions(-Wall)
endif()


###########################
# SEARCH FOR DEPENDENCIES #
###########################
set(CMAKE_MODULE_PATH
	"${PROJECT_SOURCE_DIR}/CMake"
)

set(ClanLib_MAJOR_VERSION 2)
set(ClanLib_MINOR_VERSION 2)
FIND_PACKAGE(ClanLib COMPONENTS App Core Display GL MikMod Sound Vorbis REQUIRED)
FIND_PACKAGE(OpenNI REQUIRED)


############
# INCLUDES #
############
include_directories(${PROJECT_SOURCE_DIR}/../src)
include_directories(${OPENNI_INCLUDE})
include_directories(${ClanLib_INCLUDE_DIRS})


##########
# SOURCE #
##########
# Search for cpp-files
aux_source_directory(${PROJECT_SOURCE_DIR}/../src SOURCE_FILES)

#########
# BUILD #
#########
add_executable(MagnetoPong ${SOURCE_FILES})

target_link_libraries(MagnetoPong ${OPENNI_LIBRARY})
target_link_libraries(MagnetoPong ${ClanLib_LIBRARIES})

if(UNIX)
	target_link_libraries(MagnetoPong pthread)
	target_link_libraries(MagnetoPong X11)
	target_link_libraries(MagnetoPong Xft)
	target_link_libraries(MagnetoPong freetype)
endif(UNIX)
