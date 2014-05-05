CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
# Include this File to help us to search for dependencies
INCLUDE(${CMAKE_SOURCE_DIR}/cmake/LibFindMacros.cmake)
#INCLUDE(${CMAKE_SOURCE_DIR}/cmake/FindOS.cmake)
#
#
# Name the Project
PROJECT(myro-cpp)
SET(MYRO_PKG_VER_MAJOR 2)
SET(MYRO_PKG_VER_MINOR 3)
SET(MYRO_PKG_VER_PATCH 0)
SET(PKG_VERSION "${MYRO_PKG_VER_MAJOR}.${MYRO_PKG_VER_MINOR}.${MYRO_PKG_VER_PATCH}")
SET(PKG_DESC "C++ port of the IPRE Myro Library supporting control of the Scribbler Robot & IPRE Fluke")

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PKG_DESC}")
SET(CPACK_PACKAGE_VENDOR "John Hoare" and "Richard Edwards")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.txt")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")
SET(CPACK_PACKAGE_VERSION_MAJOR "${MYRO_PKG_VER_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${MYRO_PKG_VER_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${MYRO_PKG_VER_PATCH}")
INCLUDE(CPack)

IF(WIN32)
SET(GUI_LIBRARIES gdi32)
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Dcimg_OS=2")
ELSE(WIN32)
FIND_PACKAGE(X11 REQUIRED)
SET(GUI_LIBRARIES ${X11_LIBRARIES})
ENDIF(WIN32)


# Build included libjpeg library...
#FIND_PACKAGE(JPEG REQUIRED)
#INCLUDE_DIRECTORIES(${JPEG_INCLUDE_DIRS})
add_subdirectory(jpeg)
INCLUDE_DIRECTORIES(${MYROCPPJPEG_SOURCE_DIR})


#set(Boost_DEBUG TRUE)
#set(Boost_USE_STATIC_LIBS ON)
# Check for Boost Threading Library
SET(Boost_USE_MULTITHREADED ON)
SET(Boost_DETAILED_FAILURE_MSG TRUE)
FIND_PACKAGE(Boost REQUIRED)
#FIND_PACKAGE(Boost COMPONENTS thread NO_MODULE)
#MESSAGE(STATUS "INCLUDES: ${Boost_INCLUDE_DIRS}")
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
#TODO: Try to fix this, this is a hack because I can't get the FIND_PACKAGE for boost to actually find
# the threading library, despite it being installed. It looks like a common problem, because player 
# appears to do the same thing.
IF (NOT Boost_THREAD_FOUND)
SET (Boost_THREAD_LIBRARY boost_thread-mt)
ENDIF (NOT Boost_THREAD_FOUND)

#MESSAGE(STATUS "Threading Found?: ${Boost_THREAD_FOUND}")
#MESSAGE(STATUS "LIBRARIES: ${Boost_LIBRARIES}")
#MESSAGE(STATUS "Thread: ${Boost_THREAD_LIBRARY}")

# DOXYGEN
FIND_PACKAGE(Doxygen)
IF(DOXYGEN_FOUND)
  MESSAGE(STATUS "Doxygen Found, Building Documentation. Run ccmake to turn off.")
  OPTION(BUILD_DOCS "Build the Doxygen Documentation" ON)
ELSE(DOXYGEN_FOUND)
  MESSAGE(STATUS "Doxygen NOT found, not building doxygen documentation.")
  OPTION(BUILD_DOCS "Build the Doxygen Documentation" OFF)
ENDIF(DOXYGEN_FOUND)
OPTION(FULL_DOCS "Build Complete Documentation (Including Private Methods)" OFF)
IF (DOXYGEN_DOT_FOUND)
  SET(HAVE_DOT YES)
ELSE (DOXYGEN_DOT_FOUND)
  SET(HAVE_DOT NO)
ENDIF (DOXYGEN_DOT_FOUND)

IF (FULL_DOCS)
  SET(BUILD_FULL_DOCS YES)
ELSE (FULL_DOCS)
  SET(BUILD_FULL_DOCS NO)
ENDIF (FULL_DOCS)

IF (BUILD_DOCS)
  CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in"
                 "${CMAKE_CURRENT_BINARY_DIR}/docs/Doxyfile"
                 IMMEDIATE @ONLY)
  ADD_CUSTOM_TARGET(doc ALL "${DOXYGEN_EXECUTABLE}" "${CMAKE_CURRENT_BINARY_DIR}/docs/Doxyfile")
  INSTALL( DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/docs/html/" DESTINATION "share/doc/myro-cpp-${PKG_VERSION}/html" )
ENDIF (BUILD_DOCS)
# END DOXYGEN

# Make uninstall target
CONFIGURE_FILE(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
        "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")


add_subdirectory(src)
add_subdirectory(headers)
add_subdirectory(test)
