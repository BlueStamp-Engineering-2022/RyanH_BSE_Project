# Omni-Directional Robot
Hi, my name is Ryan, and I am a rising senior at Monta Vista High School.

| **Engineer** | **School** | **Area of Interest** | **Grade** |
|:--:|:--:|:--:|:--:|
| Ryan | Monta Vista High School | Mechanical Engineering | Incoming Senior

![Headstone Image] (https://lh3.googleusercontent.com/pw/AM-JKLVd_RKZXDbv-9g-FS4-osAxcADfkAJQNDwSvj-4HLe3SLbJkhEs4QIhtkNCkso6Rn3e1cpVuookS0rVkaK18u0loLw12V1pWRHJRzcbV0mqgZxWiuNL220krBZol0HZ02rpaTCKz8qWuoyVamOBqag=s950-no?authuser=0)
  
# Final Milestone
My final milestone is the increased reliability and accuracy of my robot. I ameliorated the sagging and fixed the reliability of the finger. As discussed in my second milestone, the arm sags because of weight. I put in a block of wood at the base to hold up the upper arm; this has reverberating positive effects throughout the arm. I also realized that the forearm was getting disconnected from the elbow servo’s horn because of the weight stress on the joint. Now, I make sure to constantly tighten the screws at that joint. 

[![Final Milestone](https://res.cloudinary.com/marcomontalbano/image/upload/v1612573869/video_to_markdown/images/youtube--F7M7imOVGug-c05b58ac6eb4c4700831b2b3070cd403.jpg )](https://www.youtube.com/watch?v=F7M7imOVGug&feature=emb_logo "Final Milestone"){:target="_blank" rel="noopener"}

# Second Milestone
My final milestone is the increased reliability and accuracy of my robot. I ameliorated the sagging and fixed the reliability of the finger. As discussed in my second milestone, the arm sags because of weight. I put in a block of wood at the base to hold up the upper arm; this has reverberating positive effects throughout the arm. I also realized that the forearm was getting disconnected from the elbow servo’s horn because of the weight stress on the joint. Now, I make sure to constantly tighten the screws at that joint.

[![Third Milestone](https://res.cloudinary.com/marcomontalbano/image/upload/v1612574014/video_to_markdown/images/youtube--y3VAmNlER5Y-c05b58ac6eb4c4700831b2b3070cd403.jpg)](https://www.youtube.com/watch?v=y3VAmNlER5Y&feature=emb_logo "Second Milestone"){:target="_blank" rel="noopener"}
# First Milestone
  

It has been 6 days since I started on the Omni-directional robot, and I’ve managed to successfully pair the PS2 remote with the wireless adapter and get all of the electrical components working, As of right now, only the PS2 controller’s forward-backwards key pad buttons are operational. Pressing the “forward” key pad button allows all three VEX motors to rotate in a clockwise fashion, while pressing the “backwards” key pad button allows all three VEX motors to rotate in a counter-clockwise fashion. 

The circuit that I have completed include a battery pack, a breadboard, an Arduino, a PS2 wireless adapter, two motor drivers, and three 2-wire VEX motors. Two power the three motors, I connected the two wires that extend from the battery pack into their respective positive and negative positions on the breadboard. From there, I connected two wires into the Arduino (one into the ‘vin’ pin and the other into the ground pin) that extend from the breadboard. The reason why I didn’t plug the wires into the 5V or 3.3 V pins on the Arduino is because the motors required more voltage to run. Therefore, plugging the wires into the ‘vin’ pin was equivalent to plugging it into a wall socket (in our case, the battery pack), which would supply enough power to run the motors. All the other wires that extend from the breadboard are plugged into the correct positive/negative positions on the motor drivers. From each motor driver, two wires are allocated to power each VEX motor. The other wires that run from the IN1 - IN4, ENA, and ENB pins are plugged into the digital pins on the Arduino. Most notably, the ENA and ENB pins control the speed the motors are rotating at, meaning the wires that run from these pins must be plugged into a digital pin with the ‘~’ sign as this sign indicates PWM can be used. Finally, the wires from the PS2 wireless adapter are all plugged into the analog pins on the Arduino with the exception of the two wires that power the adapter. One of the wires that power the adapter are plugged into the 3.3V pin, while the other is plugged into the ground pin. 

The biggest challenge that I faced was pairing the PS2 controller with the wireless adapter. Unfortunately, the wireless adapter was not compatible with the wires that I had to my disposal. As a result, I had to remove the casing that surrounded the adapter and directly solder each wire into their correct positions on the circuit board. This took quite a while to complete. After that, I tried coding for the Arduino so that the motors would move following inputs from the PS2 controller. However, although the code I wrote compiled successfully, the PS2 controller inputs had no effect on the motors. Luckily, the issue was not in the code I had written, but rather the library (PS2x_lib) I had installed. To solve the problem, all I had to do was install a different library for the Arduino, and that allowed for the motors to respond to the PS2 controller inputs. 


[![First Milestone](https://res.cloudinary.com/marcomontalbano/image/upload/v1612574117/video_to_markdown/images/youtube--CaCazFBhYKs-c05b58ac6eb4c4700831b2b3070cd403.jpg)](https://www.youtube.com/watch?v=CaCazFBhYKs "First Milestone"){:target="_blank" rel="noopener"}

# Starter Project: TV-B-Gone 


My starter project was the TV-B-Gone, which, upon pressing a button located at the bottom left of the circuit board, will turn off most TVs of American/Asian origin. 

The TV-B-Gone uses 4 LEDs (located at the front of the device) to emit IR pulses and send an IR code to the targeted TV. IR pulses travel at a frequency of 38 KHz, and this is the type of frequency my targeted TV recognizes. If the TV recognizes the IR code, it will turn off. The TV-B-Gone is battery operated, and all its components are soldered onto a PCB. A PCB is known as a printed circuit board and has both conductive and insulating layers. The PCB has two wires that extend from a battery holder soldered into the bottom of the PCB. The batteries supply the power for the device, and the wires allow for the electrical current to reach the PCB. From there, when the button is pressed, a green LED indicator will blink to signal that IR pulses are emitting. The LED indicator light is controlled by the microcontroller, which was inserted into an 8-pin socket. Using resistors, capacitors, oscillators (which produce an oscillating electronic signal), and transistors (a device used to switch or amplify electrical signals), the 4 LEDs at the front of the device are then prompted to emit the IR pulses. 

The main challenge I faced was soldering. Prior to the first day of BSE, I had no experience in soldering. Unsurprisingly, when I initially started, I was progressing at a very slow/inefficient pace, and my soldering work was, to say the least, rough. However, as I progressed, I got better at soldering, and towards the end, I was able to solder at a pretty efficient pace. 


[![Ryan H Starter Project](https://res.cloudinary.com/marcomontalbano/image/upload/v1655500204/video_to_markdown/images/youtube--NJntLOVBBz4-c05b58ac6eb4c4700831b2b3070cd403.jpg)](https://www.youtube.com/watch?v=NJntLOVBBz4 "Ryan H Starter Project")





