#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//Called this way, shield uses default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

// default value for servo out of 4096
// want 0.5-2.5 (or 1-2) ms out of 20 ms
// (b/c of 50 hz update)
// so about 205-410 out of 4096 is safe range to start testing.
int J0startingValue = 308;
int J1startingValue = 300;
int J2startingValue = 300;
int EEstartingValue = 300;

// Set servo pwm values to 'safe middle' values to begin testing their ranges.
// Setting servos to extreme values can strip gears and damage robot.
int J0currentValue = J0startingValue;
int J1currentValue = J1startingValue;
int J2currentValue = J2startingValue;
int EEcurrentValue = EEstartingValue;

// declare incomingByte
int incomingByte = 0;

void setup() {
  Serial.begin(115200);

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ); // Analog servos run at ~50 hz updates

  delay(10); // delay for 10 ms

  // put servo in assumed 'middle' position
  pwm.setPWM(0,0,J0currentValue);
  pwm.setPWM(1,0,J1currentValue);
  pwm.setPWM(2,0,J2currentValue);
  pwm.setPWM(3,0,EEcurrentValue);
  

}

void loop() {
  // put your main code here, to run repeatedly:

// send data only when you receive data: 
  if (Serial.available() > 0) { 
    // read the incoming byte: 
    incomingByte = Serial.read();

    // say what you got: 
    Serial.println(incomingByte, DEC);

    // print the current x, y, z value
    Serial.print("J0 pwm value: "); Serial.println(J0currentValue);
    Serial.print("J1 pwm value: "); Serial.println(J1currentValue);
    Serial.print("J2 pwm value: "); Serial.println(J2currentValue);
    Serial.print("EE pwm value: "); Serial.println(EEcurrentValue);
    
    switch (incomingByte) {
      case 'a':  // adjust pwm value out of 4096 until servo just fails to actuate, then bring it back a step
        J0currentValue += 4;
        break;
      case 'd':
        J0currentValue -= 4;
        break;
      case 'w':  // adjust pwm value out of 4096 until servo just fails to actuate, then bring it back a step
        J1currentValue += 4;
        break;
      case 's':
        J1currentValue -= 4;
        break;
      case 'r':  // adjust pwm value out of 4096 until servo just fails to actuate, then bring it back a step
        J2currentValue += 4;
        break;
      case 'f':
        J2currentValue -= 4;
        break;
      case 'q':  // adjust pwm value out of 4096 until servo just fails to actuate, then bring it back a step
        EEcurrentValue += 4;
        break;
      case 'e':
        EEcurrentValue -= 4;
        break;  
      case 'h':  // reset pwm values to those representing the starting configuration 
        J0currentValue = J0startingValue;
        J1currentValue = J1startingValue;
        J2currentValue = J2startingValue;
        EEcurrentValue = EEstartingValue;
        break;  
    }

    // Set the pwm values for each servo
    pwm.setPWM(0,0,J0currentValue);
    pwm.setPWM(1,0,J1currentValue);
    pwm.setPWM(2,0,J2currentValue);
    pwm.setPWM(3,0,EEcurrentValue);
    
    }
   
}
