find_package (Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
include_directories (${TEST_SOURCE_DIR}/src
                     ${Boost_INCLUDE_DIRS}
                     )
add_definitions (-DBOOST_TEST_DYN_LINK)

# Add executable
add_executable (DriverSensorTest DriverSensorTest.cpp)

# Add Link Libraries
target_link_libraries (DriverSensorTest
                      AgroPiLib
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

# Add Tests
add_test (NAME Driver_Sensor_Test COMMAND DriverSensorTest)
#add_test (NAME Architecture_Tests  COMMAND ArchitectureTest)
#add_test (NAME Integration_Tests   COMMAND IntegrationTest)

