cmake_minimum_required(VERSION 3.0)

project(watertank)

set(CMAKE_BUILD_TYPE Debug)
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

# Load Python Libraries
# ---------------------
# a.) use Python 2.7 to avoid version conflicts
find_package(PythonLibs)
# b.) use Python 3 from the distro (same distro used on the target)
# find_package(PythonLibs 3)
# c.) use pyenv to manually install a version matching the Python version on the target distro https://realpython.com/intro-to-pyenv/
# set(PYTHON_INCLUDE_PATH ~/.pyenv/versions/3.5-dev/include/python3.5m)
# set(PYTHON_LIBRARIES ~/.pyenv/versions/3.5-dev/lib/libpython3.5m.so)

include_directories(${PYTHON_INCLUDE_PATH})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_SWIG_FLAGS "")

set(WATERTANK_SOURCES
    libwatertank.c
    libwatertank.i
    exos_watertank.c
    )

set_source_files_properties(${WATERTANK_SOURCES} PROPERTIES CPLUSPLUS ON)

swig_add_module(libWaterTank python ${WATERTANK_SOURCES})
swig_link_libraries(libWaterTank ${PYTHON_LIBRARIES} zmq exos-api)

set(WATERTANK_MODULE_FILES
    build/_libWaterTank.so
    build/libWaterTank.py
    )

install(FILES ${WATERTANK_MODULE_FILES} DESTINATION /home/user/watertank)

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME exos-comp-watertank)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "WaterTank summary")
set(CPACK_PACKAGE_DESCRIPTION "Some description")
set(CPACK_PACKAGE_VENDOR "Your Company")

set(CPACK_PACKAGE_VERSION_MAJOR 1)
set(CPACK_PACKAGE_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION_PATCH 0)
set(CPACK_PACKAGE_FILE_NAME exos-comp-watertank_1.0.0_amd64)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Your Name")

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)

