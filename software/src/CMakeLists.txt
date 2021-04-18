#set( CMAKE_VERBOSE_MAKEFILE on )
# Specify minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the project name and version
project(AgroPi VERSION 0.1)

set(cpprestsdk_DIR /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}/cmake/)
find_package(cpprestsdk REQUIRED)

# Locate libraries and headers
find_package(Threads REQUIRED)
find_library(LIB_I2C i2c REQUIRED)
find_package( CURL )
find_package( OpenCV REQUIRED )

# Set Include Directories
set(INCLUDE_DIRS
   ${CMAKE_CURRENT_SOURCE_DIR}
   ${CMAKE_CURRENT_SOURCE_DIR}/utils
   ${CMAKE_CURRENT_SOURCE_DIR}/threads
   ${CMAKE_CURRENT_SOURCE_DIR}/controller
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials
   ${OpenCV_INCLUDE_DIRS}
)

# Set Source files
set(SOURCES  
   ${CMAKE_CURRENT_SOURCE_DIR}/utils/utils.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/utils/CppTimer.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/Sampler.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials/I2CDriver.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials/GPIODriver.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials/SHT31D.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials/Camera.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials/RelayBoard.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials/SGP30.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials/VEML7700.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/Controller.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/threads/ControllerThread.cpp
)

# Set Header files 
set(HEADERS
   ${CMAKE_CURRENT_SOURCE_DIR}/utils/utils.h
   ${CMAKE_CURRENT_SOURCE_DIR}/utils/CppTimer.h
   ${CMAKE_CURRENT_SOURCE_DIR}/utils/CppTimerCallback.h
   ${CMAKE_CURRENT_SOURCE_DIR}/utils/typeDefinitions.h 
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials/I2CSensor.h
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials/I2CDriver.h
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials/GPIODriver.h
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials/SHT31D.h
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials/Camera.h
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials/RelayBoard.h
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials/SGP30.h
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials/VEML7700.h
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/Controller.h
   ${CMAKE_CURRENT_SOURCE_DIR}/threads/ControllerThread.h
   ${CMAKE_CURRENT_SOURCE_DIR}/controller/Sampler.h
)

# Create library for src and test
add_library(AgroPiLib SHARED ${SOURCES} )
target_include_directories(AgroPiLib PUBLIC ${INCLUDE_DIRS})
target_link_libraries(AgroPiLib i2c rt fcgi++ fcgi ${CMAKE_THREAD_LIBS_INIT} curl ${OpenCV_LIBS} ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials/I2CSensor.h)
target_link_libraries(AgroPiLib cpprestsdk::cpprest) 

# Add executable
add_executable(AgroPi main.cpp)

# Link libraries to executable

target_link_libraries(AgroPi AgroPiLib)
