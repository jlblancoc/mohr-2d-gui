PROJECT(mohr2d)


CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

IF(CMAKE_COMPILER_IS_GNUCXX)
	# High level of warnings.
	# The -Wno-long-long is required in 64bit systems when including sytem headers.
 	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -Wno-write-strings")
 	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-long-long -Wno-write-strings")

	IF(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
	ENDIF()
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

IF (MSVC)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
ENDIF()


# Use MRPT:
FIND_PACKAGE( MRPT REQUIRED opengl gui)

# wx:
# wx:
# Select wx toolkit options, like GTK2 vs GTK3, etc.
if(UNIX)
	# If available, prefer gtk3:
	execute_process(
		COMMAND wx-config --selected-config --toolkit=gtk3
		RESULT_VARIABLE ret
		OUTPUT_QUIET
	)
	if(ret EQUAL "0")
		message(STATUS "wxWidgets: Found gtk3 version, using it.")
		set(wxWidgets_CONFIG_OPTIONS_DEFAULT "--toolkit=gtk3")
	else()
		message(STATUS "wxWidgets: No gtk3 version found, falling back to default (likely gtk2)")
	endif()
	unset(ret)

	set(wxWidgets_CONFIG_OPTIONS "${wxWidgets_CONFIG_OPTIONS_DEFAULT}" ON STRING "wxWidgets toolkit options")
endif()

SET(wxWidgets_USE_LIBS base core gl adv aui )
FIND_PACKAGE(wxWidgets REQUIRED)
INCLUDE(${wxWidgets_USE_FILE})

# Add the required libraries for linking:
INCLUDE_DIRECTORIES( ${wxWidgets_INCLUDE_DIRS} )

# ---------------------------------------------
# TARGET:
# ---------------------------------------------
SET(SRCS
	mohr_2dApp.cpp mohr_2dApp.h
	mohr_2dMain.cpp mohr_2dMain.h
	MyGLCanvas.h
	)
IF(WIN32)
	SET(SRCS ${SRCS} resource.rc)
ENDIF(WIN32)

# Define the executable target:
ADD_EXECUTABLE(${PROJECT_NAME} WIN32 ${SRCS})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${wxWidgets_LIBRARIES}  ${MRPT_LIBRARIES})

