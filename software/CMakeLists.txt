# Specify minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the project name and version
project(AgroPi VERSION 0.1)

# Include Direcotries
include_directories(threads)
include_directories(controller)
include_directories(controller/peripherials)
#include_directories("./threads" "./controller")
 
# Specify Include Paths
set(includes "./controller/peripherials/SHT31D.cpp" "./controller/peripherials/Camera.cpp" "./controller/peripherials/CCS811.cpp" "./controller/peripherials/VEML7700.cpp" "./controller/Controller.cpp" "./controller/Actuator.cpp" "./threads/AgroPiThread.cpp" "./threads/ServerThread.cpp") 

# Add the executablep
add_executable(AgroPi ${includes} main.cpp)

# Locate libraries and headers
find_package(WiringPi REQUIRED)
find_package(Threads REQUIRED) 

# Include headers
include_directories(${WIRINGPI_INCLUDE_DIRS}) 

# Link against libraries
target_link_libraries(AgroPi ${WIRINGPI_LIBRARIES}) 
target_link_libraries(AgroPi ${CMAKE_THREAD_LIBS_INIT})

# Configure Header files to pass the version number to the source code
#configure_file(TutorialConfig.h.in TutorialConfig.h)
