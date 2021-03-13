(ignore '```' dashes these only indicate block of the code)


~Getting Required Packages~

	
	sudo apt-get update
	sudo apt-get upgrade
	sudo apt-get install git
	sudo apt-get install cmake
	sudo apt-get install flex
	sudo apt-get install bison
	sudo apt-get install wiringpi
	sudo apt-get install libboost-all-dev
	sudo apt-get install libi2c-dev
	

~Setting Up Git Account~
	
	git config --global user.email "email"
	git config --global user.name "username"
	 

~Setting up cmake file for wiringPi~
create a fille called FindWiringPi.cmake with the following and put it in /usr/share/cmake-3.x/Modules

	
	find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
	find_path(WIRINGPI_INCLUDE_DIRS NAMES wiringPi.h)

	include(FindPackageHandleStandardArgs)
	find_package_handle_standard_args(wiringPi DEFAULT_MSG WIRINGPI_LIBRARIES WIRINGPI_INCLUDE_DIRS)
	

~Installing Doxygen~ (Prerequisites cmake, python, flex, bison)
1. Clone Repo
	```
	git clone https://github.com/doxygen/doxygen.git
	cd doxygen
	```
2. Make
	```
	mkdir build
	cd build
	cmake -G "Unix Makefiles" ..
	make
	```
3. Install
	```
	sudo make install
	```

~To Generate doxygen Documentation~
1. Go to the software folder and run:
``` 
doxygen Doxyfile 
``` 


~Building project~
1. Go to software folder
2. Run Following set of commands, this creates folder build changes to it and runs CMake file from software folder
```
	mkdir build
	cd build/
	cmake ..
	make test ARGS="-V"  
	make
```