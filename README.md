# Automatic Uniaxial Tensiometer
Aka: Test-Yo-Limit

Provide a short description of the following:
1. **Repository Contents:** 
2. **System Parts:** 
3. **Software Dependencies:** 

## Repository Contents
Explain what is contained in this repository. You don't need to state the obvious, but it's important to mention anything custom or unique to your project.  For example, 3D models (STL) files, etc...  This repository should contain everything needed to replicate your design. 
- **Item 1:** Arduino IDE code. Sufficient to operate the entirety of the tensiometer
- **Item 2:** MATLAB script for post-data processing. Automatically generates stress vs. strain curve from raw force and elongation data 
- **Item 3:** Presentation materials as well as documentation of the entirety of the process 

## System Parts 
Parts and equipement used in our system as well as where the items can easily be found
- **Part 1:** Stepper motor & driver - $65 [Amazon Link](https://www.amazon.com/gp/product/B012QFRKAO/ref=ppx_yo_dt_b_asin_title_o05_s00?ie=UTF8&psc=1)
- **Part 2:** Arduino Microcontroller - $22 [Amazon Link](https://www.amazon.com/Arduino-A000066-ARDUINO-UNO-R3/dp/B008GRTSV6/ref=sr_1_3?crid=3VL1MZU82I7D&keywords=arduino&qid=1651766056&s=industrial&sprefix=arduino%2Cindustrial%2C91&sr=1-3)
- **Part 3:** 16x2 LCD Screen I2C - $8 [Amazon Link](https://www.amazon.com/ALMOCN-Display-Interface-Backlight-MEGA2560/dp/B08LYHC7CQ/ref=sr_1_5?crid=XXKXR0GDMG4I&keywords=lcd+screen+16x2&qid=1651766111&s=industrial&sprefix=lcd+screen+16x2%2Cindustrial%2C54&sr=1-5)
- **Part 4:** Joystick (for navigation) - $8 [Amazon Link](https://www.amazon.com/Active-Piezo-Buzzer-Module-SunFounder/dp/B014KQLE8Q/ref=sr_1_3?keywords=joystick+arduino&qid=1651766199&s=industrial&sprefix=joystick+%2Cindustrial%2C64&sr=1-3)
- **Part 5:** 20 kg Load Cell - $8 [Amazon Link](https://www.amazon.com/Weighing-Amplifier-Pressure-Portable-Electronic/dp/B09NNYFY3F/ref=sr_1_3?crid=B2ZRQ3387ERW&keywords=20+kg+load+cell&qid=1651767942&s=industrial&sprefix=20kg+load+cell%2Cindustrial%2C66&sr=1-3)

## Software Dependencies
Indicate any libraries or special configuration options that need to be installed/configured to run your software.  Provide links.  We should be able to follow your instructions below to run your software on different machine. 
- **Dependency 1:** AccelStepper; Arduino Library - Open source library available on Arduino IDE allowing easy control over virtually any stepper motor connected to your microcontroller 
- **Dependency 2:** LiquidCrstal; Arduino Library - Open source library available on Arduino IDE allowing easy control over non-I2C LCD screens

Farid Barak, Alex Reyes, Lee Kihyun, Nour El Banna