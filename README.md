## ESP32-based 4-channel moving head RGB lighting fixture

![Sparky GIF](Images/sparky.gif)

## Features

- **Art-Net for LEDs**
  - RGB LEDs can be controlled and synced to music using [LedFx](https://github.com/LedFx/LedFx) or any other software that supports Art-Net.

- **Smartphone App**
  - Servo movements and preprogrammed movements can be played through the Sparky built with MIT App Inventor.
  - The app talks to the ESP32 via UDP.

  ![APP](Images/app1.png)
  ![APP](Images/app2.png)

## Hardware

- ESP32 microcontroller  
- PCA9685 16-channel servo driver  
- 8 servo motors (4 pan + 4 tilt)  
- IRLZ44N MOSFET to control the LEDs.
- 300ma RGB LEDs  

## YouTube Video

[![YouTube Video](https://img.youtube.com/vi/QPc3wm93dXg/0.jpg)](https://www.youtube.com/watch?v=QPc3wm93dXg)
