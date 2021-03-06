cmake_minimum_required(VERSION 3.4.1)


# 根据编译系统，定义宏 Windows 或 Linux
MESSAGE(STATUS "operation system is ${CMAKE_HOST_SYSTEM_NAME}")
IF (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Windows")
    ADD_DEFINITIONS(-DWindows)
ELSE (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Linux")
    ADD_DEFINITIONS(-DLinux)
ENDIF ()


# SETUP_OPENCV
ADD_DEFINITIONS(-DUSE_OPENCV)
SET(OPENCV_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/main/opencv_3_4_0)
MESSAGE("OPENCV_PATH: " ${OPENCV_PATH})

## include head files
SET(OPENCV_INC_DIR ${OPENCV_PATH}/include)
INCLUDE_DIRECTORIES(${OPENCV_INC_DIR})

## config OPENCV340_LIBS
SET(OPENCV340_LIBS)
SET(OPENCV_LIBS_PATH ${OPENCV_PATH}/libs/${ANDROID_ABI})
SET(OPENCV_3rdPARTY_PATH ${OPENCV_PATH}/3rdparty/libs/${ANDROID_ABI})

FILE(GLOB OPENCV_LIBS "${OPENCV_LIBS_PATH}/*.a")
FILE(GLOB OPENCV_3rdPARTY_LIBS "${OPENCV_3rdPARTY_PATH}/*.a")
LIST(APPEND OPENCV340_LIBS ${OPENCV_LIBS})
LIST(APPEND OPENCV340_LIBS ${OPENCV_3rdPARTY_LIBS})
LIST(APPEND OPENCV340_LIBS
    -Wl,--start-group
    ${OPENCV340_LIBS}
    -Wl,--end-group
    )
MESSAGE("OPENCV340_LIBS: " ${OPENCV340_LIBS})


# LOCAL PROJECT
SET(PROJECT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp)
## include
INCLUDE_DIRECTORIES(${PROJECT_PATH}/inc)
## src
FILE(GLOB SRC_LIST "${PROJECT_PATH}/src/*.cpp")

## output lib
ADD_LIBRARY(native-lib
            SHARED
            ${SRC_LIST} )
TARGET_LINK_LIBRARIES(native-lib
                      ${OPENCV340_LIBS}
                      log )