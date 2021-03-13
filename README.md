<h2 align="center">AgroPi</h2>  
<p align="center">
  <a href="https://github.com/krogk/AgroPi">
    <img src="media/images/logo1.png" alt="Logo" >
  </a>
  
  <p align="center">
    Learn cultivatiion of plants or fungus through a Raspberry Pi driven environment monitoring system. 
    <br />
</div>

<p align="center">
  <a href="https://twitter.com/agropiofficial">
    <img src="media/images/icon_twitter.png" alt="Twitter"  width="64" height="64">
  </a>
  <a href="https://github.com/krogk/AgroPi">
    <img src="media/images/icon_youtube.png" alt="YouTube"  width="64" height="64">
  </a>
  <a href="https://www.instagram.com/agropiofficial/">
    <img src="media/images/icon_ig.png" alt="Instagram"  width="64" height="64">
  </a>
  <a href="https://www.facebook.com/AgroPiOfficial">
    <img src="media/images/icon_facebook.png" alt="Facebook"  width="64" height="64">
  </a>


<!-- TOC -->
<details open="open">
  <summary><h2 style="display: inline-block">Contents</h2></summary>
  <ol>
    <li>
      <a href="#about">About</a>
      <ul>
        <li><a href="#software">Software</a></li>
        <li><a href="#hardware">Hardware</a></li>
        <li><a href="#roadmap">Roadmap</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
        <li><a href="#usage">Usage</a></li>
      </ul>
    </li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#wiki">Wiki</a></li>
  </ol>
</details>

<!-- Project descirption -->
## About

AgroPi is an educational tool which allows user to learn in detail how changes in enviroment effect plant's health.  
<br />
<br />
Website interface enables user to easily display and control the conditions within enviromental chamber in real time. 
The information throughout your grow cycle is saved in a grow log so you can share it with other users, so they can copy the exact conditions you've specifed within a click of a button. In addition a photography of the contents of your cultivation system is taken in specified intervals. 
<br />
<br />
AgroPi will use AI driven image pocessing to determine whether your plants are heatlhy and if not specify what is wrong.

<div align="center">

[![Contributors](https://img.shields.io/github/contributors/krogk/AgroPi.svg?style=for-the-badge)](https://github.com/krogk/AgroPi/graphs/contributors)
[![Forks](https://img.shields.io/github/forks/krogk/AgroPi.svg?style=for-the-badge)](https://github.com/krogk/AgroPi/network/members)
[![Stars](https://img.shields.io/github/stars/krogk/AgroPi.svg?style=for-the-badge)](https://github.com/krogk/AgroPi/stargazers)
[![Issues](https://img.shields.io/github/issues/krogk/AgroPi.svg?style=for-the-badge)](https://github.com/krogk/AgroPi/issues)
[![License](https://img.shields.io/github/license/krogk/AgroPi.svg?style=for-the-badge)](https://github.com/krogk/AgroPi/blob/main/LICENSE)

<br />

  <a href="https://github.com/krogk/AgroPi">
    <img src="media/images/agropitopright.PNG" alt="Concept Render" >
  </a>


</div>

### Software

Website interface will allow you to view:
* Temperature
* Humidity
* Light Level
* Moisture of the soil
* Ph of the soil
* Photography of the system
<br />
As well as to easily set the target values for each variable for particular time of day.
<br />

Camera module:  


### Hardware

* [Raspberry Pi 4 Model B](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
<br />

Sensors:
* [Raspberry Pi Camera Rev 1.3 Lens: P5V04A, Cable: AWM 20624]()
* [Thermometer + Humidity - SHT31D](https://github.com/krogk/AgroPi/blob/main/hardware/SHT31D/Sensirion_Humidity_SHT3x_Datasheet_digital-767294.pdf)
* [Light - VEML7700](https://github.com/krogk/AgroPi/blob/main/hardware/VEML7700/veml7700.pdf)
* [Gas - SGP30]()


<br />

Actuators:
* [Camera Actuators - TBD]()
* [Water Pump](https://www.mybotic.com.my/products/Micro-Submersible-Water-Pump-DC-3V-5V/2778#:~:text=Suction%20Distance%3A%200.8%20meter%20)
* [Fan - TBD]()

Misc:
* [Relay Board - TBD]()

<br />

Schematics:
* [System Schematic - TBC]()


### Roadmap

[x] Github Setup
<br />
<br />
[] Working core prototype
* [x] I2C Driver
* [x] Light Sensor integrated
* [] Temperature + Humidity Sensor integrated
* [] Camera sensor integrated
* [] Gas Sensor
* [] Web server
* [] Real-time Adaptation
[] Initial software release 
<br />
<br />
[] Image processing using AI - prototype
* [] Gather training dataset
* [] Train neuralnet
* [] Test on real samples
<br />
<br />

[] Life cycle assessment & comparison
<br />
<br />


<!-- Getting Started -->
## Getting Started

### Prerequisites

...Ubuntu Packages: 
  ```sh
  sudo apt-get update
	sudo apt-get upgrade
	sudo apt-get install git
	sudo apt-get install cmake
	sudo apt-get install flex  - (Only Required for building Doxygen)
	sudo apt-get install bison - (Only Required for building Doxygen)
	sudo apt-get install libboost-all-dev
	sudo apt-get install libi2c-dev
  ```


### Installation

1. Clone the repository
   ```sh
   git clone https://github.com/krogk/AgroPi
   ```
2. Build
   ```sh
	  mkdir build
	  cd build/
	  cmake ..
	  make test ARGS="-V"  
	  make
   ```

<!-- Usage -->
### Usage

To run the software:
1. Go to build directory
  ```sh
  ./src/AgroPi 
 ```


<!-- Contributing -->
## Contributing

See `CONTRIBUTING` for more information.

<!-- License -->
## License

Distributed under the GPL-3.0 License. See `LICENSE` for more information.


<!-- Contact Info -->
## Contact

[Samuel Obosu](https://github.com/Samuel-Obosu)
<br />
[Andrew Scott-George](https://github.com/andrewsg3)
<br />
[Kamil Rog](https://github.com/krogk)


<!-- AgroPi Wiki -->
## Wiki

[Wiki](https://github.com/krogk/AgroPi/wiki)
