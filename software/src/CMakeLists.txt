# Specify minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the project name and version
project(AgroPi VERSION 0.1)

include_directories(threads)
include_directories(controller) 
include_directories(controller/peripherials)
include_directories("./threads" "./controller")

# Specify Include Paths
#set(includes "./controller/peripherials/SHT31D.cpp" "./controller/peripherials/Camera.cpp" "./controller/peripherials/CCS811.cpp" "./controller/peripherials/VEML7700.cpp" "./controller/Controller.cpp" "./controller/Actuator.cpp" "./threads/AgroPiThread.cpp" "./threads/ServerThread.cpp") 
#set(includes "./controller/Controller.cpp" "./controller/Actuator.cpp" "./threads/AgroPiThread.cpp" "./threads/ServerThread.cpp") 

# Add libs
add_library( SHT31D ./controller/peripherials/SHT31D.cpp ./controller/peripherials/SHT31D.h) 
add_library( Camera ./controller/peripherials/Camera.cpp ./controller/peripherials/Camera.h) 
add_library( CCS811 ./controller/peripherials/CCS811.cpp  ./controller/peripherials/CCS811.h)
add_library( VEML7700 ./controller/peripherials/VEML7700.cpp ./controller/peripherials/VEML7700.h ) 
add_library( Controller ./controller/Controller.cpp ./controller/Controller.h)
add_library( Actuator ./controller/Actuator.cpp ./controller/Actuator.h)
add_library( agropithreads ./threads/AgroPiThread.cpp ./threads/AgroPiThread.h ./threads/ServerThread.cpp ./threads/ServerThread.h)

target_include_directories(SHT31D     PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials)
target_include_directories(Camera     PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials)
target_include_directories(CCS811     PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials)
target_include_directories(VEML7700   PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/controller/peripherials)
target_include_directories(Controller PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/controller)
target_include_directories(Actuator   PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/controller)
target_include_directories(agropithreads PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/threads)

# Locate libraries and headers
find_package(WiringPi REQUIRED)
find_package(Threads REQUIRED) 

# Include headers
include_directories(${WIRINGPI_INCLUDE_DIRS}) 

# Add the executable
#add_executable(AgroPi ${includes} main.cpp)
add_executable(AgroPi main.cpp)

# Link against libraries
target_link_libraries(AgroPi  ${WIRINGPI_LIBRARIES}) 
target_link_libraries(AgroPi  ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(AgroPi  Actuator agropithreads  Controller  VEML7700 SHT31D Camera CCS811  )
