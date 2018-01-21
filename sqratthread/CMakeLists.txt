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

SET(CMAKE_MACOSX_RPATH ON)

## Apply coverity patch to Squirrel?
SET(WORKING_DIR WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

## build list of source files

FILE(GLOB SQRATTHREAD_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
FILE(GLOB SQRATTHREAD_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)

INCLUDE_DIRECTORIES(${SQUIRREL_INCLUDE_DIRS} ${SQRAT_INCLUDE_DIRS})

# the squirrel sources are out of our control so don't be too pedantic about
# them
SET(CMAKE_CXX_FLAGS "")
SET(CMAKE_C_FLAGS "")

## define a target for building the library

LIST(SORT SQRATTHREAD_SOURCES)
ADD_LIBRARY(sqratthread SHARED ${SQRATTHREAD_SOURCES})

# use standardized variable name
set(LIB_SUBDIR "lib${LIB_SUFFIX}"
	CACHE STRING "Subdirectory of prefix into which libraries are installed (e.g., lib32, lib64)")

IF(SQUIRREL_IS_SUBPROJECT)
	IF(BUILD_SHARED_LIBS)
		INSTALL(TARGETS sqratthread
			RUNTIME DESTINATION bin
			LIBRARY DESTINATION ${LIB_SUBDIR})
	ENDIF()
ELSE()
	INSTALL(TARGETS sqratthread
		RUNTIME DESTINATION bin
		ARCHIVE DESTINATION ${LIB_SUBDIR}
		LIBRARY DESTINATION ${LIB_SUBDIR}
		COMPONENT sqrat)
ENDIF()
