# Specify minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the project name and version
project(AgroPi VERSION 0.1)

# Add the executable
add_executable(AgroPi AgroPiThread.cpp ServerThread.cpp main.cpp)

#
find_package (Threads)

#
target_link_libraries (AgroPi ${CMAKE_THREAD_LIBS_INIT})

# Configure Header files to pass the version number to the source code
#configure_file(TutorialConfig.h.in TutorialConfig.h)

