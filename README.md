# FLTK External Project Build

This project demonstrates building FLTK 1.4.4 as a static library using CMake's ExternalProject_Add.

## Build Instructions

```bash
mkdir build
cd build
cmake ..
make -j$(nproc)
```

## Run Test

```bash
./fltk_test
```

The test application will open a window with a button. Clicking the button will change the text in the box above it.

## Requirements

- CMake 3.12 or higher
- C++ compiler
- Git
- X11 development libraries (Linux)
- Platform-specific dependencies:
  - Linux: libx11-dev, libxext-dev, libxinerama-dev, libxcursor-dev, libxrender-dev, libxfixes-dev, libxft-dev
  - macOS: Xcode command line tools
  - Windows: MinGW or MSVC
