<h2 align="center">AgroPi</h2>  
<p align="center">
  <a href="https://github.com/krogk/AgroPi">
    <img src="media/images/logo1.png" alt="Logo" >
  </a>
  
  <p align="center">
    Learn cultivation of plants and mushrooms through a Raspberry Pi driven monitoring system. 
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

AgroPi is a flexible modular educational tool which allows user to learn how changes in enviroment effect plant's/mushroom's health. It is up to the user to decide what actuators fit the enviromental chamber needs best.   
<br />
<br />
Website interface enables user to easily display and control the conditions within enviromental chamber in real time. 
The information throughout your grow cycle is saved in a grow log which you can share with other users so they can copy the exact conditions you've specifed with a click of a button. In addition AgroPi takes photos of your growth in constant intervals so you can show off your crops. 
<br />
<br />
In the near future AgroPi is going to utilize AI driven image pocessing to determine whether your plants are heatlhy and if not specify what might be the issue. Future updates will focus on recognizing stages of growth and nutrient defficiencies. 

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

In the first software release we plan to allow you to view the following conditions on the website interface:
* Temperature 
* Humidity
* Light Intensity
* TVOC
* eCO2
* Photos of your crops
<br />
<br />
As well as easily set the target values for each variable for particular time of day, however, the actuation is going to be implemented in software release 2.
<br />


### Hardware

* [Raspberry Pi 4 Model B](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
<br />

Sensors:
* [Raspberry Pi Camera Rev 1.3 Lens: P5V04A, Cable: AWM 20624]()
* [Thermometer + Humidity - SHT31D](https://github.com/krogk/AgroPi/blob/main/hardware/SHT31D/Sensirion_Humidity_SHT3x_Datasheet_digital-767294.pdf)
* [Light - VEML7700](https://github.com/krogk/AgroPi/blob/main/hardware/VEML7700/veml7700.pdf)
* [Gas - SGP30](https://github.com/krogk/AgroPi/blob/main/hardware/SGP30/SGP30%20Datasheet.pdf)


<br />

Actuators - This is user's choice however for our demo the following are used:
* [Heating Element - Zerodis PTC Heating Element AC/DC 12V (80 ℃ 2—5W) ](https://www.amazon.co.uk/gp/product/B07FJZQLMK/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1)
* [Water Pump](https://www.mybotic.com.my/products/Micro-Submersible-Water-Pump-DC-3V-5V/2778#:~:text=Suction%20Distance%3A%200.8%20meter%20)
* [Fan - Coolermaster A12025-12CB-3BN-F1]()
<br />
Misc:
* [Relay Board - Elego ](https://github.com/krogk/AgroPi/blob/Software_Release_1/hardware/Relay%20Board/4%20CHANNEL%205V%2010A%20RELAY%20MODULE.pdf)

<br />

Schematics:
* [System Schematic - TBC]()


### Roadmap
<br />
[x] Github Setup
<br />
<br />
[-] Software Release 1 - Working core prototype
* [x] I2C Driver
* [x] Light Sensor Integrated
* [x] Temperature + Humidity Sensor Integrated
* [x] Gas Sensor Integrated
* [-] Camera Integrated
* [80%] Web server
* [30%] Real-time Adaptation
   </a>
<br />
<br />
[-] Software Release 2 - Actuation & Image Processing - Detecting Mold
* [-] Relay Board Integration
* [-] Lighting Actuation
* [-] Heating Actuation
* [-] Airflow Actuation
* [-] Watering Actuation
* [-] Water Level Sensor Integrated
* [-] Gather Training Dataset
* [-] Train neuralnet
* [-] Test on real samples
<br />
<br />
[-] Software Release 3 - Life cycle Assessment & Nutrient Defficiencies
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
1. Go to build directory and run
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

[Samuel Obosu - Web server & Network Programming](https://github.com/Samuel-Obosu)
<br />
[Andrew Scott-George - Image Processing](https://github.com/andrewsg3)
<br />
[Kamil Rog - Real-time Embedded Programming](https://github.com/krogk)


<!-- AgroPi Wiki -->
## Wiki

[Wiki](https://github.com/krogk/AgroPi/wiki)
