cmake_minimum_required(VERSION 3.10)
project(ekwos LANGUAGES C)

file(GLOB_RECURSE SOURCES "src/*.c")

# Create the executable
add_executable(ekwos ${SOURCES})

# Set include directories (if any)
target_include_directories(ekwos PRIVATE src)

target_link_libraries(ekwos PRIVATE glfw vulkan)

target_compile_options(ekwos PRIVATE
	-g
	-Wall
	-Wextra
	-Wshadow
	-DDEBUG=1
	-Wpedantic
)

set_target_properties(ekwos PROPERTIES
	C_STANDARD 17
)
