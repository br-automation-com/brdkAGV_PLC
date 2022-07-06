cmake_minimum_required(VERSION 3.0)

project(ros_topics_typ)

set(CMAKE_BUILD_TYPE Debug)
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

# Load Python Libraries
# ---------------------
# a.) use Python 3 
find_package(PythonLibs 3)
# b.) use Python 2.7 (  change the Runtime service command to 'python2' in the .exospkg file)
# - update the DEPENDS to python-dev
# find_package(PythonLibs 2)
# c.) use pyenv to manually install a version matching the Python version on the target distro https://realpython.com/intro-to-pyenv/
# set(PYTHON_INCLUDE_PATH ~/.pyenv/versions/3.9-dev/include/python3.9)
# set(PYTHON_LIBRARIES ~/.pyenv/versions/3.9-dev/lib/libpython3.9.so)

include_directories(${PYTHON_INCLUDE_PATH})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_SWIG_FLAGS "")

set(ROS_TOPICS_TYP_SOURCES
    libros_topics_typ.c
    libros_topics_typ.i
    exos_ros_topics_typ.c
    )

set_source_files_properties(${ROS_TOPICS_TYP_SOURCES} PROPERTIES CPLUSPLUS ON)

swig_add_module(libros_topics_typ python ${ROS_TOPICS_TYP_SOURCES})
swig_link_libraries(libros_topics_typ ${PYTHON_LIBRARIES} zmq exos-api)

set(ROS_TOPICS_TYP_MODULE_FILES
    build/_libros_topics_typ.so
    build/libros_topics_typ.py
    )

install(FILES ${ROS_TOPICS_TYP_MODULE_FILES} DESTINATION /home/user/ros_topics_typ)

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME exos-comp-ros_topics_typ)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "ros_topics_typ summary")
set(CPACK_PACKAGE_DESCRIPTION "Some description")
set(CPACK_PACKAGE_VENDOR "Your Company")

set(CPACK_PACKAGE_VERSION_MAJOR 1)
set(CPACK_PACKAGE_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION_PATCH 0)
set(CPACK_PACKAGE_FILE_NAME exos-comp-ros_topics_typ_1.0.0_amd64)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Your Name")

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)

