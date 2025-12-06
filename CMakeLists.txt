cmake_minimum_required(VERSION 3.12)
project(FLTK_External_Build)

include(ExternalProject)

set(FLTK_PREFIX "${CMAKE_BINARY_DIR}/fltk-prefix")
set(FLTK_INSTALL_DIR "${FLTK_PREFIX}/install")

ExternalProject_Add(fltk_external
    GIT_REPOSITORY https://github.com/fltk/fltk.git
    GIT_TAG release-1.4.4
    GIT_SHALLOW TRUE
    PREFIX ${FLTK_PREFIX}
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${FLTK_INSTALL_DIR}
        -DCMAKE_BUILD_TYPE=Release
        -DFLTK_BUILD_SHARED_LIBS=OFF
        -DFLTK_BUILD_TEST=OFF
        -DFLTK_BUILD_EXAMPLES=OFF
        -DFLTK_BUILD_FLUID=ON
        -DFLTK_BUILD_FLTK_OPTIONS=OFF
        -DFLTK_BUILD_GL=OFF
        -DFLTK_BACKEND_WAYLAND=OFF
        -DFLTK_BACKEND_X11=ON
        -DFLTK_GRAPHICS_CAIRO=OFF
        -DFLTK_USE_PANGO=OFF
        -DFLTK_OPTION_PRINT_SUPPORT=OFF
        -DFLTK_OPTION_SVG=OFF
        -DFLTK_OPTION_FILESYSTEM_SUPPORT=ON
        -DFLTK_BUILD_HTML_DOCS=OFF
        -DFLTK_BUILD_PDF_DOCS=OFF
    BUILD_COMMAND ${CMAKE_COMMAND} --build . --config Release
    INSTALL_COMMAND ${CMAKE_COMMAND} --install . --config Release
)

# Create test executable
add_executable(fltk_test test.cpp)
add_dependencies(fltk_test fltk_external)

# Set include directories
target_include_directories(fltk_test PRIVATE ${FLTK_INSTALL_DIR}/include)

# Link FLTK libraries
if(WIN32)
    target_link_libraries(fltk_test PRIVATE
        ${FLTK_INSTALL_DIR}/lib/libfltk.a
        ${FLTK_INSTALL_DIR}/lib/libfltk_images.a
        comctl32
        ws2_32
        gdi32
        ole32
        uuid
    )
elseif(APPLE)
    target_link_libraries(fltk_test PRIVATE
        ${FLTK_INSTALL_DIR}/lib/libfltk.a
        ${FLTK_INSTALL_DIR}/lib/libfltk_images.a
        "-framework Cocoa"
        "-framework ApplicationServices"
    )
else()
    # Linux with X11 backend
    # use X11 backend for minimal dependencies

    find_package(X11 REQUIRED)
    if(NOT X11_Xrender_FOUND)
        find_library(X11_Xrender_LIB Xrender)
    endif()
    if(NOT X11_Xfixes_FOUND)
        find_library(X11_Xfixes_LIB Xfixes)
    endif()
    if(NOT X11_Xcursor_FOUND)
        find_library(X11_Xcursor_LIB Xcursor)
    endif()

    target_link_libraries(fltk_test PRIVATE
        ${FLTK_INSTALL_DIR}/lib/libfltk.a
        ${FLTK_INSTALL_DIR}/lib/libfltk_images.a
        ${X11_LIBRARIES}
        ${X11_Xrender_LIB}
        ${X11_Xfixes_LIB}
        ${X11_Xcursor_LIB}
        pthread
        dl
        m
    )
endif()
