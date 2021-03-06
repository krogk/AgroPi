# Specify minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the project name and version
project(AgroPi VERSION 0.1)

# Include Direcotries
add_subdirectory(src)

# Enable Testing
enable_testing ()

# Add Test directory
add_subdirectory(test)


#add_test (NAME AgroPiTest COMMAND Test)