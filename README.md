# Draw Robot Mimic

In the figure below, what you see is a LEGO Spike Prime connected to two motors. The motors turn are connected to two arms. When the end effector is moved around the positions and angles of the motors are read in and stored in lists. Then the motors will return to the setup to the position it was in when it started reading in values using a proportional controller with a Kp value of 2. After this the SPIKE will iterate through the list of positions and angles. The positions are sent to the motors to be re-run, and the angles are sent to the WIO which are used to display a twin on its Screen. The WIO is constantly looking for communication from the SPIKE PRIME. If it gets a message it will try to Parse it into what should be two angles. If successful, it will then update the information of all of the arms by using forward kinematics, and once it is done with that, it will display the arms on the WIO Screen.

[Full Video](https://youtu.be/WViitAMiYTg)
## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

- Install the current upstream Arduino IDE at the 1.8.13 level or later. The current version is on the [Arduino website](https://www.arduino.cc/en/main/software).
- A SEEED WIO Terminal [Purchase One Here.](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
  - Install the libraries required to run Arduino on the SEEED WIO Terminal. [Get Started with Wio Terminal.](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/)
- Required Arduino Libraries
  - [TFT](https://www.arduino.cc/en/Reference/TFTLibrary) (Version 1.0.6 or Newer)
  - [Adafruit_GFX](https://github.com/adafruit/Adafruit-GFX-Library) (Version 1.10.4 or Newer)
- A LEGO SPIKE PRIME Kit [Purchase One Here.](https://education.lego.com/en-us/products/lego-education-spike-prime-set/45678#spike%E2%84%A2-prime)
  - The LEGO SPIKE PRIME kit IDE should be downloaded to update the firmware [here](https://education.lego.com/en-us/downloads/spike-prime/software)
    - Once the firmware is updated you can connect via Serial Communication using Putty or [this IDE](https://github.com/chrisbuerginrogers/ME35_21)

### Installing

Simply download the files in this repository and first run the code on the WIO Terminal using the Arduino IDE. Then run the SPIKE PRIME Code in REPL or the IDE that can be found here, [SPIKE PRIME IDE](https://github.com/chrisbuerginrogers/ME35_21).

### Setup Notes

## Demo

### [Live Copy](https://media.giphy.com/media/Wjpp8uTFGSXqaPxPWP/giphy.gif)

### [Mimic](https://media.giphy.com/media/YPpXbbER1qSMeWwRI4/giphy.gif)

## Authors

- **Sawyer Bailey Paccione** - *WIO CODE, SPIKE CODE* - [Portfolio](http://sawyerbaileypaccione.tech/)
- **Joshua Fitzgerald** - *Physical Design*

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

![Demonstration of Functionality](https://media.giphy.com/media/i8xavPDAaiKVibUfea/giphy.gif)
