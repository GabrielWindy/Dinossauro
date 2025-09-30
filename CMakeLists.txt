cmake_minimum_required(VERSION 3.16)
project(Dinossauro)

if(NOT CMAKE_BUILD_TYPE)
  set(default_build_type "Debug")
  message(STATUS "Set the build type to `${default_build_type}` as none was specified.")
  set(CMAKE_BUILD_TYPE ${default_build_type} CACHE STRING "Chooce the build type." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
  "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
message(STATUS "Dinossauro Build Type: ${CMAKE_BUILD_TYPE}")

# Set the version for Dinossauro
set(Dinossauro_Version_Major 0)
set(Dinossauro_Version_Minor 1)
set(Dinossauro_Version_Patch 0)
set(Dinossauro_Version_Status "-dev")
set(PROJECT_VERSION
  "${Dinossauro_Version_Major}.${Dinossauro_Version_Minor}.${Dinossauro_Version_Patch}${Dinossauro_Version_Status}"
)
message(STATUS "${PROJECT_NAME} version: ${PROJECT_VERSION}")

set(SOURCES 
  ./src/main.c
)

add_executable(
  dino
  ${SOURCES}
) 

target_link_libraries(
  dino
  PRIVATE
  raylib
)

add_custom_command(TARGET dino POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:dino>/assets

)
