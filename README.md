<h2 align="center">AgroPi</h2>  

  <p align="center">
    <img src="" alt="Logo" width="" height="">
  </a>
  
  <p align="center">
    Learn indoor cultivation of plants & mushrooms through a Raspberry Pi enabled environment monitor & regulator. 
    <br />
</div>

<!-- TOC -->
<details open="open">
  <summary><h2 style="display: inline-block">Contents</h2></summary>
  <ol>
    <li>
      <a href="#about">About</a>
      <ul>
        <li><a href="#software">Software</a></li>
        <li><a href="#hardware">Hardware</a></li>
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
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#wiki">Wiki</a></li>
  </ol>
</details>

<!-- Project descirption -->
## About

AgroPi is an educational Raspberry Pi driven enviroment to
    <br />
AgroPi uses a website interface which allows user display and control the conditions within your enviromental chamber in real time.
    <br />
The information throughout your grow cycle is saved so you can share it with other users, which can copy the exact conditions you specifed within a click of a button. 

Our Website: [AgroPi](https://agropi.co.uk)

### Software

Spoilage Recognition
<br />
### Hardware

AgroPi uses following set of sensors:

* [Raspberry Pi 4 Model B](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
* [Camera]()
* [Thermometer]()
* [Humidity Sensor]()
* [Water Pump]()
* [Relay Board]()
* [Schematic]()


<!-- Getting Started -->
## Getting Started

### Prerequisites

Packages 
* cmake
  ```sh
  sudo apt-get install cmake
  ```

### Installation

1. Clone the repository
   ```sh
   git clone https://github.com/krogk/AgroPi
   ```
2. Run auto configuration script
   ```sh
   ./autoconf
   ```
3. Compile
    ```sh
   make 
   ```
4. Flashing
    ```sh
   upload -p /dev/ttyUSB0 --fqbn rpi4:rpi4:AgroPi
   ```

<!-- Usage -->
### Usage

AgroPi 

<!-- License -->
## License

Distributed under the GPL-3.0 License. See `LICENSE` for more information.


<!-- Contact Info -->
## Contact


[@Samuel Obosu](2607374o@student.gla.ac.uk)
<br />
[@Andrew Scott-George](2238090s@student.gla.ac.uk)
<br />
[@Kamil Rog](2536572r@student.gla.ac.uk)



<!-- AgroPi Wiki -->
## Wiki

[Wiki]()
