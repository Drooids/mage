cmake_minimum_required(VERSION 3.0)
project(Mage)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Project constants.
set(Mage_VERSION_MAJOR 1)
set(Mage_VERSION_MINOR 0)

configure_file(
	"${PROJECT_SOURCE_DIR}/cmake/configuration.hpp.in"
	"${PROJECT_BINARY_DIR}/include/configuration.hpp"
)

set(Mage_INCLUDE_PATH "${PROJECT_SOURCE_DIR}/include/mage")
set(Mage_SOURCE_FILES "${PROJECT_BINARY_DIR}/include/configuration.hpp")

# Parse the CMakeLists files in the subdirectories now.
add_subdirectory(src)
add_subdirectory(test)