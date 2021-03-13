#set( CMAKE_VERBOSE_MAKEFILE on )
# Specify minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the project name and version
project(AgroPi VERSION 0.1)

# Locate libraries and headers
find_package(Threads REQUIRED)
find_library(LIB_I2C i2c)

# Set Include Directories
set(INCLUDE_DIRS
   ${WIRINGPI_INCLUDE_DIRS}
   ${CMAKE_CURRENT_SOURCE_DIR}/threads
   ${CMAKE_CURRENT_SOURCE_DIR}/controller
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials
)

# Set Source files
set(SOURCES  
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/Controller.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials/I2CDriver.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials/SHT31D.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials/Camera.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials/CCS811.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials/VEML7700.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/Actuator.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/threads/ServerThread.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/threads/AgroPiThread.cpp
)

# Set Header files 
set(HEADERS
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/Controller.h
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials/I2CDriver.h
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials/SHT31D.h
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials/Camera.h
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials/CCS811.h
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials/VEML7700.h
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/Actuator.h
   ${CMAKE_CURRENT_SOURCE_DIR}/threads/ServerThread.h
   ${CMAKE_CURRENT_SOURCE_DIR}/threads/AgroPiThread.h
)

# Create library for src and test
add_library(AgroPiLib SHARED ${SOURCES})
target_include_directories(AgroPiLib PUBLIC ${INCLUDE_DIRS})
target_link_libraries(AgroPiLib i2c ${CMAKE_THREAD_LIBS_INIT})

# Add the executable
add_executable(AgroPi main.cpp)

# Link libraries to executable
target_link_libraries(AgroPi AgroPiLib)
