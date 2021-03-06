find_package (Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
include_directories (${TEST_SOURCE_DIR}/src
                     ${Boost_INCLUDE_DIRS}
                     )
add_definitions (-DBOOST_TEST_DYN_LINK)

# Locate libraries and headers
find_package(WiringPi REQUIRED)
find_package(Threads REQUIRED) 

# Include headers
include_directories(${WIRINGPI_INCLUDE_DIRS}) 

add_executable (Test test.cpp)

# Link against libraries
target_link_libraries(Test ${WIRINGPI_LIBRARIES}) 
target_link_libraries(Test ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries (Test
                       VEML7700
                       ${Boost_FILESYSTEM_LIBRARY}
                       ${Boost_SYSTEM_LIBRARY}
                       ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                       )
add_test (NAME AgroPiTest COMMAND Test)
