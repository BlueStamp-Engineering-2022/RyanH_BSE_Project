#include <SoftwareSerial.h>
#include <PS2X_lib.h>  
#include <HampelFilter.h>

// Field variables for each motor pin and EN pin
int motor1pin1 = 2;
int motor1pin2 = 4;
int motor1EN = 3;

int motor2pin1 = 6;
int motor2pin2 = 7;
int motor2EN = 5;

int motor3pin1 = 9;
int motor3pin2 = 10;
int motor3EN = 11;

int motorSpeed = 0; // Holds the motor speed for rotational direction
double lJoyXD = 0.0; // Holds the x-coordinate of the left joystick input
double lJoyYD = 0.0; // Holds the y-coordinate of the right joystick input
int motor1Speed = 0; // Holds the speed of motor 1
int motor2Speed = 0; // Holds the speed of motor 2
int motor3Speed = 0; // Holds the speed of motor 3

boolean greenLight = false; // Becomes true when joystick values are not outliers (allows for commencement of main code)
boolean bluetoothMode = false; // Used to toggle bluetooth mode (renders ps2 controller useless when bluetooth is connected)
boolean arrowRotation = false; // Used to determine when voice control isn't used

// Booleans for each direction 
boolean forward = false;
boolean backwards = false;
boolean moveRight = false;
boolean moveLeft = false;
boolean rRight = false;
boolean rLeft = false;
boolean stopped = false; 
boolean stoppedRRight = false; // Boolean for whether to stop rotating to the right
boolean stoppedRLeft = false; // Boolean for whether to stop rotating to the left

// Hampelfilter object initialized.
// Values: HampelFilter( <default value>, <window size (range)>, <threshold for outlier detection (sensitivity)> )
//                                                               The lower the value, the more aggressive.
//                                                               The higher the value, the less aggressive.
HampelFilter leftX = HampelFilter(0.00, 3, 100);
HampelFilter leftY = HampelFilter(0.00, 3, 100);

HampelFilter rightX = HampelFilter(0.00, 3, 120);
HampelFilter rightY = HampelFilter(0.00, 3, 120);

SoftwareSerial bluetooth (8,12); // Allows for serial communication (sending data one bit at a time) across these digital pins
char command = 'h';
char bluetoothStatus = 'p';

PS2X ps2x; // Create PS2 Controller Class

int error = 0; // Holds error as an int
byte type = 0; // Variable for type of controller
byte vibrate = 0; // Variable for vibration of controller

void setup() 
{
  // Sets the pin mode of each pin on the Arduino (input or output pin)
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(motor3pin1, OUTPUT);
  pinMode(motor3pin2, OUTPUT);

  pinMode(motor1EN, OUTPUT);
  pinMode(motor2EN, OUTPUT);
  pinMode(motor3EN, OUTPUT);

 // Sets serial communication at 9600 bits/sec
 Serial.begin(9600);
 bluetooth.begin(9600);
  
 error = ps2x.config_gamepad(A3,A1,A2,A0, false, true);   // Setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) 
                                                          // Checks for error.
     
 // Check for error    
    
  if(error == 0){      
    Serial.println("Found Controller, configured successful");      
  }      
  else if(error == 1)      
    Serial.println("No controller found, check wiring or reset the Arduino");      
  else if(error == 2)      
    Serial.println("Controller found but not accepting commands");         
  else if(error == 3)      
    Serial.println("Controller refusing to enter Pressures mode, may not support it.");     
     
  // Check for the type of controller       
  type = ps2x.readType();       
  switch(type) {      
    case 0:      
      Serial.println("Unknown Controller type");      
      break;      
    case 1:      
      Serial.println("DualShock Controller Found");      
      break;      
    case 2:      
      Serial.println("GuitarHero Controller Found");      
      break;      
  }
}

void loop() 
{
  error = ps2x.config_gamepad(A3,A1,A2,A0, false, true); // Continues to check if controller is connected or not

  // If no controller is found, stop all motors and return to setup()
  if (error == 1)
  {
    analogWrite(motor1EN, 0);
    analogWrite(motor2EN, 0);
    analogWrite(motor3EN, 0);
    return;
  }
  else 
  {
    ps2x.read_gamepad(false, vibrate); // Controller will not vibrate

    // Checks if bluetooth is available
    if (bluetooth.available())
    {
       command = bluetooth.read(); // Reads the information received via bluetooth

      // Depending on commands, bluetoothMode is set to true or false
      // Determines whether to take control away from ps2 controller or not
      if (command == 'c')
        bluetoothMode = true;
      else if (command == 'a')
        arrowRotation = true;
      else if (command == 'w')
        arrowRotation = false;
      else if (command == 'n')
      {
        bluetoothMode = false;
        arrowRotation = false;
      }

      // When voice control is being used, booleans for each direction
      // are set accordingly
      if (bluetoothMode == true && arrowRotation == false)
      {
        if (command == 'f')
        {
          forward = true;
          stopped = false;
          backwards = false;
          moveLeft = false;
          moveRight = false;
          rLeft = false;
          rRight = false;
        }
        else if (command == 'b')
        {
          backwards = true;
          stopped = false;
          forward = false;
          moveLeft = false;
          moveRight = false;
          rLeft = false;
          rRight = false;
        }
        else if (command == 'l')
        {
          moveLeft = true;
          stopped = false;
          forward = false;
          backwards = false;
          moveRight = false;
          rLeft = false;
          rRight = false;
        }
        else if (command == 'r')
        {
          moveRight = true;
          stopped = false;
          forward = false;
          backwards = false;
          moveLeft = false;
          rLeft = false;
          rRight = false;
        }
        else if (command == 'u')
        {
          rLeft = true;
          stopped = false;
          forward = false;
          backwards = false;
          moveLeft = false;
          moveRight = false;
          rRight = false;
        }
        else if (command == 'd')
        {
          rRight = true;
          stopped = false;
          forward = false;
          backwards = false;
          moveLeft = false;
          moveRight = false;
          rLeft = false;
        }
        
        if (command == 's')
        {
          stopped = true;
          forward = false;
          backwards = false;
          moveLeft = false;
          moveRight = false;
          rLeft = false;
          rRight = false;
        }
      }
      else if (bluetoothMode == true && arrowRotation == true) // When voice command isn't being used, set direction booleans accordingly
      {
        if (command == 'f' && rLeft == false && rRight == false)
        {
          forward = true;
          stopped = false;
          backwards = false;
          moveLeft = false;
          moveRight = false;
          rLeft = false;
          rRight = false;
        }
        else if (command == 'b' && rLeft == false && rRight == false)
        {
          backwards = true;
          stopped  = false;
          forward = false;
          moveLeft = false;
          moveRight = false;
          rLeft = false;
          rRight = false;
        }
        else if (command == 'l' && rLeft == false && rRight == false)
        {
          moveLeft = true;
          stopped = false;
          forward = false;
          backwards = false;
          moveRight = false;
          rLeft = false;
          rRight = false;
        }
        else if (command == 'r' && rLeft == false && rRight == false)
        {
          moveRight = true;
          stopped = false;
          forward = false;
          backwards = false;
          moveLeft = false;
          rLeft = false;
          rRight = false;
        }
        
        if (command == 'u')
        {
          rLeft = true;
          stoppedRLeft = false;
        }
        else if (command == 'd')
        {
          rRight = true;
          stoppedRRight = false;
        }
        
        if (command == 's')
        {
          stopped = true;
          forward = false;
          backwards = false;
          moveLeft = false;
          moveRight = false;
        }

        if (command == 'g')
        {
          stoppedRLeft = true;
          rLeft = false;
        }

        if (command == 'h')
        {
          stoppedRRight = true;
          rRight = false;
        }
      }
    }
   
    int rJoyX = ps2x.Analog(PSS_RX); // read right joystick's x coordinate
    int rJoyY = ps2x.Analog(PSS_RY); // read right joystick's y coordinate

    int lJoyX = ps2x.Analog(PSS_LX); // read left joystick's x coordinate
    int lJoyY = ps2x.Analog(PSS_LY); // read left joystick's y coordinate

    // Maps the joystick (lowest value is not -255 (not 0) and highest value is not 255)
    rJoyX = map(rJoyX, 0, 255, -255, 255);
    rJoyY = map(rJoyY, 0, 255, 255, -255);
    lJoyX = map(lJoyX, 0, 255, -255, 255);
    lJoyY = map(lJoyY, 0, 255, 255, -255);

    // Deadzone for joysticks (prevents jittering and false inputs)
    if ((lJoyX > -5 && lJoyX < 13) || bluetoothMode == true)
      lJoyX = 0;
    if ((lJoyY > -8 && lJoyY < 10) || bluetoothMode == true)
      lJoyY = 0;

    if ((rJoyX > -4 && rJoyX < 4) || bluetoothMode == true)
      rJoyX = 0;
    if ((rJoyY > -4 && rJoyY < 4) || bluetoothMode == true)
      rJoyY = 0;

   // Adding joystick values to the hampelfilter for outlier detection  
   leftY.write(lJoyY); 
   leftX.write(lJoyX);

   rightY.write(rJoyY);
   rightX.write(rJoyX);

   // Checks for outliers. If there are outliers, greenLight is false, and inputs are
   // disregarded. Otherwise, inputs are taken in.
   if (leftY.checkIfOutlier(lJoyY) == true || leftX.checkIfOutlier(lJoyX) == true || 
      rightX.checkIfOutlier(rJoyX) == true || rightY.checkIfOutlier(rJoyY) == true)
   {
      greenLight = false;
   }
   else
      greenLight = true;
   
    float L = (sqrt( ( (float) lJoyY * (float) lJoyY) + ((float) lJoyX * (float) lJoyX) )); // magnitude of the left joystick components
                                                                                            // (hypotenuse of right triangle)
    L = L*0.66666666666; // Magnitude is multiplied by constant (decreases motor speed -- more controllable -- less unwanted rotation)
    float radian = (atan2((float) lJoyY, (float) lJoyX)); // Angle formed by left joystick input (angle of direction)

    // Formula for each motor's speed depending on direction and magnitude given by left joystick
    motor1Speed = (int) (L * cos( (60*(M_PI/180)) - radian )); 
    motor2Speed = (int) (L * cos( (300*(M_PI/180)) - radian ));
    motor3Speed = (int) (L * cos( (180*(M_PI/180)) - radian ));

    // Code for omni (all-directional) control using left joystick
    if (rJoyX == 0 && rJoyY == 0)
    {
      if (greenLight == true)
      {
        if (motor1Speed < 0) 
        {
           motor1Speed = motor1Speed*-1;
           digitalWrite(motor1pin1, HIGH);
           digitalWrite(motor1pin2, LOW);
    
           if (lJoyX == 0 && motor1Speed == 147)
           {
              motor1Speed = 255;
           }
    
           if (motor1Speed < 0)
           {
              motor1Speed = 0;
           }
           
           analogWrite(motor1EN, motor1Speed);
        } 
        else if (motor1Speed > 0) 
        {  
           digitalWrite(motor1pin1, LOW);
           digitalWrite(motor1pin2, HIGH);
    
           if (lJoyX == 0 && motor1Speed == 147)
           { 
              motor1Speed = 255;  
           }
    
           if (motor1Speed < 0)
           {
              motor1Speed = 0;
           }
    
           analogWrite(motor1EN, motor1Speed);
        }
        else
          analogWrite(motor1EN, 0);
       
        if (motor2Speed < 0)
        {
           motor2Speed = motor2Speed*-1;
 
           digitalWrite(motor2pin1, HIGH);
           digitalWrite(motor2pin2, LOW);
    
           if (lJoyX == 0 && motor2Speed == 147)
              motor2Speed = 255;
           
           if (lJoyY != 0 && lJoyX != 0)
           {
              motor2Speed = motor2Speed + 25;
           }
           else if (lJoyY == 0 && lJoyX < 0)
           {
              motor2Speed = motor2Speed + 10;
           }
    
           if (motor2Speed > 255)
              motor2Speed = 255;
             
           analogWrite(motor2EN, motor2Speed);
        }
        else if (motor2Speed > 0)
        {
           digitalWrite(motor2pin1, LOW);
           digitalWrite(motor2pin2, HIGH);
           
           if (lJoyX == 0 && motor2Speed == 147)
              motor2Speed = 255;
              
           if (lJoyY != 0 && lJoyX != 0)
           {
              motor2Speed = motor2Speed + 5;
           }
           else if (lJoyY == 0 && lJoyX > 0)
           {
              motor2Speed = motor2Speed - 10;
           }
           else if (radian >= 2.00 && radian <= 2.59)
           {
              motor2Speed = motor2Speed + 150;
           }
    
           if (motor2Speed > 255)
              motor2Speed = 255;
    
           analogWrite(motor2EN, motor2Speed);
        }
        else
        {
          analogWrite(motor2EN, 0);
        }
        
        if (motor3Speed < 0)
        {
           motor3Speed = motor3Speed*-1;
    
           digitalWrite(motor3pin1, HIGH);
           digitalWrite(motor3pin2, LOW);
    
           analogWrite(motor3EN, motor3Speed);
        }
        else if (motor3Speed > 0)
        {
           digitalWrite(motor3pin1, LOW);
           digitalWrite(motor3pin2, HIGH);

           if (radian >= 2.00 && radian <= 2.59)
           {
              motor3Speed = motor3Speed - 50;
           }
    
           analogWrite(motor3EN, motor3Speed);
        }
        else
          analogWrite(motor3EN, 0);
      }
    }

    // Code for rotational control on right joystick
    if ((lJoyX == 0 && lJoyY == 0) || bluetoothMode == true)
    {
      if ((rJoyX < 0 && rJoyX >= -255) || rLeft == true && stopped == false 
        || rLeft == true && stoppedRLeft == false)
      {
        digitalWrite(motor1pin1, HIGH);
        digitalWrite(motor1pin2, LOW);
    
        digitalWrite(motor2pin1, HIGH);
        digitalWrite(motor2pin2, LOW);
    
        digitalWrite(motor3pin1, HIGH);
        digitalWrite(motor3pin2, LOW);

        // Checks if bluetooth mode is true and whether voice control is being used.
        // Sets the motorspeed accordingly.
        if (rLeft == false && bluetoothMode == false)
          motorSpeed = rJoyX*-1;
        else if (rLeft == true && arrowRotation == false)
          motorSpeed = 80;
        else if (rLeft == true && arrowRotation == true)
          motorSpeed = 255;
 
        if (motorSpeed <= 120)
          motorSpeed = 120;
    
        analogWrite(motor1EN, motorSpeed);
        analogWrite(motor2EN, motorSpeed);
        analogWrite(motor3EN, motorSpeed);
      }
      else if ((rJoyX > 0 && rJoyX <= 255) || rRight == true && stopped == false 
        || rRight == true && stoppedRRight == false)
      {
        digitalWrite(motor1pin1, LOW);
        digitalWrite(motor1pin2, HIGH);
    
        digitalWrite(motor2pin1, LOW);
        digitalWrite(motor2pin2, HIGH);
    
        digitalWrite(motor3pin1, LOW);
        digitalWrite(motor3pin2, HIGH);

        // Checks if bluetooth mode is true and whether voice control is being used.
        // Sets the motorspeed accordingly.
        if (rRight == false && bluetoothMode == false)
          motorSpeed = rJoyX;
        else if (rRight == true && arrowRotation == false)
          motorSpeed = 80;
        else if (rRight == true && arrowRotation == true)
          motorSpeed = 255;
          
        if (motorSpeed <= 120)
          motorSpeed = 120;
    
        analogWrite(motor1EN, motorSpeed);
        analogWrite(motor2EN, motorSpeed);
        analogWrite(motor3EN, motorSpeed);
      }
      else if ((stoppedRRight == true || stoppedRLeft == true) && bluetoothMode == true)
      {
        rRight = false;
        rLeft = false;
        
        analogWrite(motor1EN, 0);
        analogWrite(motor2EN, 0);
        analogWrite(motor3EN, 0);
      }
      else
      {
        analogWrite(motor1EN, 0);
        analogWrite(motor2EN, 0);
        analogWrite(motor3EN, 0); 
      }
    }

    // Code for forward, backwards, left, and right control via bluetooth
    if (bluetoothMode == true && rLeft == false && rRight == false)
    {
      if (stopped == false)
      {
        if (forward == true)
        {
          digitalWrite(motor1pin1, LOW);
          digitalWrite(motor1pin2, HIGH);
      
          digitalWrite(motor2pin1, HIGH);
          digitalWrite(motor2pin2, LOW);

          if (arrowRotation == false)
          {
            analogWrite(motor1EN, 110);
            analogWrite(motor2EN, 150);
            analogWrite(motor3EN, 0);
          }
          else if (arrowRotation == true)
          {
            analogWrite(motor1EN, 255);
            analogWrite(motor2EN, 255);
            analogWrite(motor3EN, 0);
          }
        }
        else if (backwards == true)
        {
          digitalWrite(motor1pin1, HIGH);
          digitalWrite(motor1pin2, LOW);
      
          digitalWrite(motor2pin1, LOW);
          digitalWrite(motor2pin2, HIGH);

          if (arrowRotation == false)
          {
            analogWrite(motor1EN, 110);
            analogWrite(motor2EN, 150);
            analogWrite(motor3EN, 0);
          }
          else if (arrowRotation == true)
          {
            analogWrite(motor1EN, 255);
            analogWrite(motor2EN, 255);
            analogWrite(motor3EN, 0);
          }
        }
        else if (moveLeft == true)
        {
          digitalWrite(motor1pin1, HIGH);
          digitalWrite(motor1pin2, LOW);
      
          digitalWrite(motor2pin1, HIGH);
          digitalWrite(motor2pin2, LOW);
      
          digitalWrite(motor3pin1, LOW);
          digitalWrite(motor3pin2, HIGH);
          
          analogWrite(motor1EN, 85);
          analogWrite(motor2EN, 95);
          analogWrite(motor3EN, 170);
        }
        else if (moveRight == true)
        {
          digitalWrite(motor1pin1, LOW);
          digitalWrite(motor1pin2, HIGH);
      
          digitalWrite(motor2pin1, LOW);
          digitalWrite(motor2pin2, HIGH);
      
          digitalWrite(motor3pin1, HIGH);
          digitalWrite(motor3pin2, LOW);
          
          analogWrite(motor1EN, 84);
          analogWrite(motor2EN, 83);
          analogWrite(motor3EN, 170);
        }
      }
      else if (stopped == true)
      {
        forward = false;
        backwards = false;
        moveLeft = false;
        moveRight = false;
        stopped = false;
        
        analogWrite(motor1EN, 0);
        analogWrite(motor2EN, 0);
        analogWrite(motor3EN, 0);
      }
    } 

    // Code for ps2 controller button pad (forward, backwards, left, and right)
    if (lJoyX == 0 && lJoyY == 0 && rJoyX == 0 && rJoyY == 0 && bluetoothMode == false)
    {
      if (ps2x.Button(PSB_PAD_UP))
      {
        digitalWrite(motor1pin1, LOW);
        digitalWrite(motor1pin2, HIGH);
    
        digitalWrite(motor2pin1, HIGH);
        digitalWrite(motor2pin2, LOW);
    
        analogWrite(motor1EN, 255);
        analogWrite(motor2EN, 255);
        analogWrite(motor3EN, 0);
      }
      else if (ps2x.Button(PSB_PAD_DOWN))
      {
        digitalWrite(motor1pin1, HIGH);
        digitalWrite(motor1pin2, LOW);
    
        digitalWrite(motor2pin1, LOW);
        digitalWrite(motor2pin2, HIGH);
        
        analogWrite(motor1EN, 255);
        analogWrite(motor2EN, 255);
        analogWrite(motor3EN, 0);
      }
      else if (ps2x.Button(PSB_PAD_LEFT))
      {
        digitalWrite(motor1pin1, HIGH);
        digitalWrite(motor1pin2, LOW);
    
        digitalWrite(motor2pin1, HIGH);
        digitalWrite(motor2pin2, LOW);
    
        digitalWrite(motor3pin1, LOW);
        digitalWrite(motor3pin2, HIGH);
        
        analogWrite(motor1EN, 85);
        analogWrite(motor2EN, 90);
        analogWrite(motor3EN, 170);
      }
      else if (ps2x.Button(PSB_PAD_RIGHT))
      {
        digitalWrite(motor1pin1, LOW);
        digitalWrite(motor1pin2, HIGH);
    
        digitalWrite(motor2pin1, LOW);
        digitalWrite(motor2pin2, HIGH);
    
        digitalWrite(motor3pin1, HIGH);
        digitalWrite(motor3pin2, LOW);
        
        analogWrite(motor1EN, 84);
        analogWrite(motor2EN, 90);
        analogWrite(motor3EN, 170);
      }
      else
      {
        analogWrite(motor1EN, 0);
        analogWrite(motor2EN, 0);
        analogWrite(motor3EN, 0);
      }
    } 
    
    delay(100); // Delay set at 100 milliseconds (reads input every 100 milliseconds)
   }
}
