#
# SuperTux - sqrat library build script
# Copyright (C) 2006 Christoph Sommer <christoph.sommer@2006.expires.deltadevelopment.de>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#

INCLUDE(ExternalProject)

SET(CMAKE_MACOSX_RPATH ON)

## Apply coverity patch to Squirrel?
SET(WORKING_DIR WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

## Add include/ to include directories

INCLUDE_DIRECTORIES(${SQUIRREL_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include/ ${CMAKE_CURRENT_BINARY_DIR})

## Fix Windows exports

INCLUDE (GenerateExportHeader)

## build list of source files

SET(SQRAT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/)
FILE(GLOB SQRAT_SOURCES sq/*.c )
FILE(GLOB SQRAT_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} include/)

OPTION(ENABLE_IMPORT_LIB "Build squirrel script interpreter with debugging options" OFF)
IF(ENABLE_IMPORT_LIB)
  FILE(GLOB IMPORT_SOURCES sqimport/*.cpp)
  SET(SQRAT_SOURCES ${SQRAT_SOURCES} ${IMPORT_SOURCES})
ENDIF(ENABLE_IMPORT_LIB)

OPTION(ENABLE_THREAD_LIB "Build sqratthread" OFF)
IF(ENABLE_THREAD_LIB)
  ExternalProject_Add(sqratthread
	SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/sqratthread
	CMAKE_ARGS
	-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
	-DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
	-DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
	-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
	-DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
	-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
	-DSQUIRREL_INCLUDE_DIRS=${SQUIRREL_INCLUDE_DIRS}
	-DSQRAT_INCLUDE_DIRS=${CMAKE_CURRENT_SOURCE_DIR}/include
	-DLIB_SUFFIX=${LIB_SUFFIX})
ENDIF(ENABLE_THREAD_LIB)

# the squirrel sources are out of our control so don't be too pedantic about
# them
SET(CMAKE_CXX_FLAGS "")
SET(CMAKE_C_FLAGS "")

## define a target for building the library

LIST(SORT SQRAT_SOURCES)
ADD_LIBRARY(sqrat ${SQRAT_SOURCES})
IF(ENABLE_IMPORT_LIB)
  TARGET_LINK_LIBRARIES(sqrat PUBLIC ${CMAKE_DL_LIBS})
ENDIF(ENABLE_IMPORT_LIB)

GENERATE_EXPORT_HEADER( sqrat
             BASE_NAME sqrat
             EXPORT_MACRO_NAME SQRAT_API
             EXPORT_FILE_NAME sqrat_Export.h
             STATIC_DEFINE sqrat_BUILT_AS_STATIC
)
# use standardized variable name
set(LIB_SUBDIR "lib${LIB_SUFFIX}"
	CACHE STRING "Subdirectory of prefix into which libraries are installed (e.g., lib32, lib64)")

IF(SQUIRREL_IS_SUBPROJECT)
	IF(BUILD_SHARED_LIBS)
		INSTALL(TARGETS sqrat
			RUNTIME DESTINATION bin
			LIBRARY DESTINATION ${LIB_SUBDIR})
	ENDIF()
ELSE()
	INSTALL(TARGETS sqrat
		RUNTIME DESTINATION bin
		ARCHIVE DESTINATION ${LIB_SUBDIR}
		LIBRARY DESTINATION ${LIB_SUBDIR}
		COMPONENT sqrat)
	INSTALL(FILES ${SQRAT_HEADERS} ${CMAKE_BINARY_DIR}/sqrat_Export.h
		DESTINATION include)
ENDIF()

if(DEFINED INSTALL_INC_DIR)
  install(DIRECTORY ${SQRAT_INCLUDE_DIR} DESTINATION ${INSTALL_INC_DIR})
endif()
