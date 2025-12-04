cmake_minimum_required(VERSION 3.10)
project(AOTCompiler)

set(CMAKE_C_STANDARD 99)

# Common sources
set(COMMON_SOURCES
	bc_reader.c
	regalloc.c
	util.c
)

# Windows x64 specific sources
set(WIN64_SOURCES
	win64/main.c
	win64/codegen_win64.c
	win64/emitter.c
)

# Include directories
include_directories(.)

# Executable
add_executable(aot ${COMMON_SOURCES} ${WIN64_SOURCES})