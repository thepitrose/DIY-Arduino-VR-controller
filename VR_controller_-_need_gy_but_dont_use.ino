

#include "Joystick.h"
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Joystick.h>



MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;
int UD, LR;


// Create Joystick
Joystick_ Joystick;

// Set to true to test "Auto Send" mode or false to test "Manual Send" mode.
//const bool testAutoSendMode = true;
const bool testAutoSendMode = false;

const unsigned long gcCycleDelta = 1000;
const unsigned long gcAnalogDelta = 25;
const unsigned long gcButtonDelta = 500;
unsigned long gNextTime = 0;
unsigned int gCurrentStep = 0;


void setup() {

 
  Joystick.setRxAxisRange(-10000, 10000);
  Joystick.setRyAxisRange(-10000, 10000);
  Joystick.setRzAxisRange(-10000, 10000);
  Joystick.setThrottleRange(0, 255);
  Joystick.setRudderRange(255, 0);


   Serial.begin(9600);
  Wire.begin();
  Joystick.begin();

  mpu.initialize();
  if (!mpu.testConnection()) 
   {
    while (1);
    }  

 pinMode(4, INPUT_PULLUP);
 pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
 pinMode(7, INPUT_PULLUP);
 pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
   pinMode(13, INPUT_PULLUP);
}

const int pinToButtonMap = 4;
int lastButtonState[9] = {0,0,0,0,0,0,0,0,0};
void loop() {


mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);


  
Joystick.setXAxis(analogRead(A0));  
Joystick.setYAxis(analogRead(A1));  


//Joystick.setRxAxis(ax);
//Joystick.setRyAxis(ay);
//Joystick.setRzAxis(az);



for (int index = 0; index < 9; index++)
  {
    int currentButtonState = !digitalRead(index + pinToButtonMap);
    if (currentButtonState != lastButtonState[index])
    {
      Joystick.setButton(index, currentButtonState);
      lastButtonState[index] = currentButtonState;
    }
  }
  



  delay(10);


}
