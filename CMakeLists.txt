cmake_minimum_required(VERSION 3.13)	# CMake version check
project(epidemic_simulation)			# Create project "epidemic_simulation"
set(CMAKE_CXX_STANDARD 14)				# Enable c++14 standard

# Add header and source files
include_directories(include)
file(GLOB SOURCE_FILES "src/*.cpp")

# Create executable
add_executable(epidemic_simulation ${SOURCE_FILES})