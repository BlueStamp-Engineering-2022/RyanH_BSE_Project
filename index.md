# Omni-Directional Robot
Hi, my name is Ryan, and I am a rising senior at Monta Vista High School. The project I decided to pick is the Omni-Directional Robot, which can essentially go in any direction without having to reorient itself. The base project required me to control the robot using a PS2 controller. However, I decided to make the robot voice controlled as well. Below outlines each milestone I achieved along with a demo video.

| **Engineer** | **School** | **Area of Interest** | **Grade** |
|:--:|:--:|:--:|:--:|
| Ryan | Monta Vista High School | Mechanical Engineering | Incoming Senior

# Say Hello to Robbie!
** I added a tray along with a rubber band barrier so objects don't fall off the tray while the robot is moving. **

[![Image1](https://photos.app.goo.gl/jsXyD4e3cK4Zp7236)]

# Final Milestone
For my final milestone, I decided to add voice control. Initially, the idea was to accomplish this over the internet using the Node MCU ESP8266. However, after re-wiring all the electrical components, and compiling the code I had on the Arduino IDE, I received a fatal error saying “avr/io.h file not found”. Upon further research, I soon learned that the ESP8266 did not contain an AVR microcontroller like the Arduino UNO, which was required for the PS2 library I had downloaded. Therefore, I had two choices. I could either rewrite my code for the PS2 controller to work with the particle photon, or I could find an alternative way to achieve voice control. Seeing that rewriting my code could take too long, I decided to do more research on Bluetooth control with an Arduino. It didn’t take long before I found a very helpful website that introduced the Bluetooth module HC-06, which could be connected to the Arduino for Bluetooth capabilities. I ended up asking the instructors to see if we had any in stock, and we did! I immediately connected the HC-06 to the Arduino and began coding for Bluetooth control. 

To do this, I first created an app through MIT app inventor. Using its built-in Bluetooth component, I was able to connect my phone to the HC-06 through the app. From there, I used block code to take in vocal commands from the user and made sure that only valid commands were accepted. If an invalid command was said, the app will tell the user to “provide a valid command”. To assist the user, I also added a page within the app that consisted of all the basic commands. Therefore, they could access these commands at any time if they were unsure about what the valid commands were. 

**SCREENSHOTS OF THE APP**

In order to have the omni-bot respond to the vocal commands, I had the app send a character, based on the command provided, to the HC-06. After that, the HC-06 would then send this information to the Arduino, which held the code I had written. Within the code, I had booleans for each direction (forward, backwards, left, right, turn right, turn left, and stop). When a certain character is received, using if-else statements, I was able to set the corresponding boolean to true. Then, based on that decision, the motors would move accordingly. After testing the voice control, I realized it was hard to stop the robot in a short amount of time. This caused a lot of problems as it made it nearly impossible to evade obstacles in time. To fix this, I added a “stop” button to the app. This allowed for quick stops when necessary. In addition, to those modifications, I also decided to take away control from the PS2 controller while the HC-06 was connected through the app. 

[![Final Milestone](https://res.cloudinary.com/marcomontalbano/image/upload/v1658525335/video_to_markdown/images/youtube--Z5iSiJXumOA-c05b58ac6eb4c4700831b2b3070cd403.jpg)](https://www.youtube.com/watch?v=Z5iSiJXumOA "Milestone 3")

# Logic Behind the Formula
Although deriving the formula was one of the harder tasks of this project, understanding how the formula works is actually quite simple. 

# Second Milestone
The date today is July 7th, 2022. It has been a little bit over 2 weeks since my last milestone and I have accomplished a lot since then. Here’s a brief rundown of what I currently have: 

    1.) I have finished most of the mechanical construction of the robot. All motors, wheels, and metal reinforcements have been mounted and secured. The only thing       
    left is the wooden tray which will be placed above the bottom plate. 
  
    2.) I have laid out all the electrical components onto the robot. The configuration of the electrical components will remain mostly the same from here on out.
 
    3.) The code is currently complete for the PS2 controller. Both joysticks and all keypad buttons are operational and dictate how the omni-bot moves. 
 
    4.) Jittering issues, random deviations, and unwanted rotations have been fixed. The robot can now move in all directions with relatively low rotation. 
  
    5.) An on/off switch has been added to the omni-bot.
    
    6.) I also finished deriving a formula that accurately calculates the required speed and direction of each motor given a direction from the PS2 controller's  
    
    joystick.
[![Milestone 2](https://res.cloudinary.com/marcomontalbano/image/upload/v1658528884/video_to_markdown/images/youtube--AEiCQfl9qKQ-c05b58ac6eb4c4700831b2b3070cd403.jpg)](https://www.youtube.com/watch?v=AEiCQfl9qKQ "Milestone 2")

# First Milestone
  

It has been 6 days since I started on the Omni-directional robot, and I’ve managed to successfully pair the PS2 remote with the wireless adapter and get all of the electrical components working, As of right now, only the PS2 controller’s forward-backward keypad buttons are operational. Pressing the “forward” keypad button allows all three VEX motors to rotate in a clockwise fashion while pressing the “backward” keypad button allows all three VEX motors to rotate in a counter-clockwise fashion. 

The circuit that I have completed includes a battery pack, a breadboard, an Arduino, a PS2 wireless adapter, two motor drivers, and three 2-wire VEX motors. Two power the three motors, I connected the two wires that extend from the battery pack into their respective positive and negative positions on the breadboard. From there, I inserted two wires into the Arduino (one into the ‘vin’ pin and the other into the ground pin) that extend from the breadboard. The reason why I didn’t plug the wires into the 5V or 3.3 V pins on the Arduino is because the motors required more voltage to run. Therefore, plugging the wires into the ‘vin’ pin was equivalent to plugging it into a wall socket (in our case, the battery pack), which would supply enough power to run the motors. All the other wires that extend from the breadboard are plugged into the correct positive/negative positions on the motor drivers. From each motor driver, two wires are allocated to power each VEX motor. The other wires that run from the IN1 - IN4, ENA, and ENB pins are plugged into the digital pins on the Arduino. Most notably, the ENA and ENB pins control the speed the motors are rotating at, meaning the wires that run from these pins must be plugged into a digital pin with the ‘~’ sign as this sign indicates PWM can be used. Finally, the wires from the PS2 wireless adapter are all plugged into the analog pins on the Arduino with the exception of the two wires that power the adapter. One of the wires that power the adapter is plugged into the 3.3V pin, while the other is plugged into the ground pin. 

The biggest challenge I faced was pairing the PS2 controller with the wireless adapter. Unfortunately, the wireless adapter was not compatible with the wires that I had at my disposal. As a result, I had to remove the casing surrounding the adapter and directly solder each wire into its correct position on the circuit board. This took quite a while to complete. After that, I tried coding for the Arduino so that the motors would move following inputs from the PS2 controller. However, although the code I wrote compiled successfully, the PS2 controller inputs had no effect on the motors. Luckily, the issue was not in the code I had written, but rather the library (PS2x_lib) I had installed. To solve the problem, all I had to do was install a different library for the Arduino, and that allowed for the motors to respond to the PS2 controller inputs. 



[![Milestone #1 Video](https://res.cloudinary.com/marcomontalbano/image/upload/v1656710570/video_to_markdown/images/youtube--j4AGbipcVsw-c05b58ac6eb4c4700831b2b3070cd403.jpg)](https://www.youtube.com/watch?v=j4AGbipcVsw "Milestone #1 Video")

# Starter Project: TV-B-Gone 


My starter project was the TV-B-Gone, which, upon pressing a button located at the bottom left of the circuit board, will turn off most TVs of American/Asian origin. 

The TV-B-Gone uses 4 LEDs (located at the front of the device) to emit IR pulses and send an IR code to the targeted TV. IR pulses travel at a frequency of 38 KHz, and this is the type of frequency my targeted TV recognizes. If the TV recognizes the IR code, it will turn off. The TV-B-Gone is battery operated, and all its components are soldered onto a PCB. A PCB is known as a printed circuit board and has both conductive and insulating layers. The PCB has two wires that extend from a battery holder soldered into the bottom of the PCB. The batteries supply the power for the device, and the wires allow for the electrical current to reach the PCB. From there, when the button is pressed, a green LED indicator will blink to signal that IR pulses are emitting. The LED indicator light is controlled by the microcontroller, which was inserted into an 8-pin socket. Using resistors, capacitors, oscillators (which produce an oscillating electronic signal), and transistors (a device used to switch or amplify electrical signals), the 4 LEDs at the front of the device are then prompted to emit the IR pulses. 

The main challenge I faced was soldering. Prior to the first day of BSE, I had no experience in soldering. Unsurprisingly, when I initially started, I was progressing at a very slow/inefficient pace, and my soldering work was, to say the least, rough. However, as I progressed, I got better at soldering, and towards the end, I was able to solder at a pretty efficient pace. 


[![Ryan H Starter Project](https://res.cloudinary.com/marcomontalbano/image/upload/v1655500204/video_to_markdown/images/youtube--NJntLOVBBz4-c05b58ac6eb4c4700831b2b3070cd403.jpg)](https://www.youtube.com/watch?v=NJntLOVBBz4 "Ryan H Starter Project")


