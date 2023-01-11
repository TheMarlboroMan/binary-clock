cmake_minimum_required(VERSION 3.5.1)

project(binary-clock)

option(BUILD_DEBUG "Build a debug release" OFF)
option(BUILD_APPIMAGE "Build for appimage, if not, a regular application will be built" OFF)

if(${BUILD_APPIMAGE})

	set(BUILD_VERSION "AppImage")
else()

	set(BUILD_VERSION "Regular")
endif()

message("Will build ${BUILD_VERSION} type")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(${BUILD_DEBUG})
	set(CMAKE_BUILD_TYPE Debug)
else()
	set(CMAKE_BUILD_TYPE Release)
endif()

add_compile_options(-Wall -Wextra -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual -Wno-deprecated -ansi -pedantic -fno-rtti)

#TODO: Should also allow for c++14

#In a system where the libs are not installed, add them.
#include_directories(../libdansdl2/include)
#include_directories(../libdansdl2-tools/include)
#include_directories(../log/include)
#include_directories(../dfw/include)
#include_directories(../tools/include)

add_subdirectory("${PROJECT_SOURCE_DIR}/src")

#add the framework dependencies
add_library(lm STATIC IMPORTED)
add_library(tools STATIC IMPORTED)
add_library(ldtools STATIC IMPORTED)
add_library(dansdl2 STATIC IMPORTED)
add_library(dfw STATIC IMPORTED)

#If the libraries are not installed, tell them where they are.
set_target_properties(tools PROPERTIES IMPORTED_LOCATION /usr/local/lib/libtools.a)
set_target_properties(lm PROPERTIES IMPORTED_LOCATION /usr/local/lib/liblm.a)
set_target_properties(dansdl2 PROPERTIES IMPORTED_LOCATION /usr/local/lib/libdansdl2.a)
set_target_properties(ldtools PROPERTIES IMPORTED_LOCATION /usr/local/lib/libldtools.a)
set_target_properties(dfw PROPERTIES IMPORTED_LOCATION /usr/local/lib/libdfw.a)

#binary...
if(${BUILD_APPIMAGE})

	if(${CMAKE_VERSION} VERSION_LESS "3.22.0") 

		add_definitions(-DAS_APPIMAGE=1)
	else()

		add_compile_definitions(AS_APPIMAGE=1)
	endif()
else()

	if(${CMAKE_VERSION} VERSION_LESS "3.22.0") 
		add_definitions(-DAS_REGULAR=1)
	else()

		add_compile_definitions(AS_REGULAR=1)
	endif()

endif()

add_executable(binary-clock "${PROJECT_SOURCE_DIR}/src/main.cpp" ${SOURCE})
set_target_properties(binary-clock PROPERTIES RUNTIME_OUTPUT_DIRECTORY build)
add_custom_command(TARGET binary-clock POST_BUILD COMMAND cp -r ../resources/* ./build)
target_include_directories(binary-clock PUBLIC "${PROJECT_SOURCE_DIR}")
target_link_libraries(binary-clock dfw tools dansdl2 ldtools lm SDL2 SDL2_ttf SDL2_mixer SDL2_image GL stdc++fs)
