
## Build Instructions

### Prerequisites
- CMake 3.10+
- or Makefile
- or gcc
- or clang
- MSVC Visual Studio Build Tools (for windows build)
- NASM assembler (for win_x86_backend_test)

### Build
```bash
# Configure
cmake -B build

# Build all
cmake --build build

# Build tests (optional, enabled by default)
cmake --build build --target win_x86_backend_test
```

### Disable Tests
```bash
cmake -B build -DBUILD_TESTS=OFF
cmake --build build
```

## Run Tests
```bash
cd build/Debug
win_x86_backend_test.exe