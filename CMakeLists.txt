cmake_minimum_required(VERSION 3.10)

project(sketchy-compiler)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add executable
add_executable(fe
	fe.c
	lexer.c
	error.c
)

# Include directories for headers
target_include_directories(fe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Add backend subdirectory
add_subdirectory(backend)

# Option to build tests
option(BUILD_TESTS "Build the test executables" ON)

if(BUILD_TESTS)
	# Add test executable
	add_executable(win_x86_backend_test tests/win_x86_backend_test.c)
	target_include_directories(win_x86_backend_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
endif()