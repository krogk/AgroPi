# File Structure

* AgroPi
    - **Hardware** - contains datasheets and schematics of hardware used
    - **media** - contains all media 
         + **images** - contains all images for the project
    - **software** - contains the src and test files for the software  filesn
      + **build** - user created, build takes place here
        + **doc** - contains documentation
            - doxygen documentation lives here 
        + **src** - Here source application is build
            + AgroPi - Executable for the application 
        + **test** - Here test application is build
      + **cmake** - contains cmake scripts 
          + StaticAnalyzers.cmake - Static Analyzer Settings (cppcheck)
      + **doc** - contains documentation
        + CMakeLists.txt - doc building
        + Doxyfile.in - doxygen settings
        + Design.md - Application Design
      + **src** - contains source files
        + **controller** - Contains sampler, contoller and peripherials 
          + **peripherials** - Contains all communication protocol, sensors and relay drivers
             + CMakeLists.txt - source building
          + Controller.h - 
          + Controller.cpp -
          + Sampler.h - 
          + Sampler.cpp -
          + httplib.h - 
        + **threads** - Contains controller thread and base cpp thread class
        + **utils** - contains base clases for timers, typedefs and maths functions
      + **test** - unit tests & integration tests
          + CMakeLists.txt - test building
          + DriverSensorTest.cpp - Unit tests for I2C driver and sensors
      + **web** - contains web application
    - README.md - main readme file
    - CMakeLists.txt - Main CMake configuration
