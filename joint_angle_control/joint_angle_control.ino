#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

// Robotic arm parameters.
// These will need to be modifed FIRST based on your arm
////// Theta 1 //////
#define J0_min  144   // min pulselength
#define J0_max  472   // max pulselength
#define d0_min  -90   // coresponding limit in degrees (min)
#define d0_max  90    // max degrees

////// Theta 2 //////
#define J1_min  148    // min pulselength
#define J1_max  388   // max pulselength
#define d1_min  0     // coresponding limit in degrees (min)
#define d1_max  135    // max degrees

////// Theta 3 //////
#define J2_min  516   // min pulselength
#define J2_max  292   // max pulselength
#define d2_min  0     // coresponding limit in degrees (min)
#define d2_max  90    // max degrees

////// End Effector //////
#define J3_min  240   // pulselength in open position
#define J3_max  392   // pulselength in closed position
#define d3_min  0     // coresponding min distance in mm
#define d3_max  53    // max distance in mm

// The setup routine runs once when you press reset:
void setup() {
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  // Initialize pwm communication
  pwm.begin();
  // Set onboard oscillator frequency
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);

  // Move the robotic arm to 'probably servo-safe' configuration
  // in case pulselength values have not been configured
  // map figures out where first argument lies between 2nd and 3rd
  // arguments, and interpolates it to the same relative position
  // between 4th and 5th arguments.
  // We use this to convert degrees to servo pulselength for pwm.
  pwm.setPWM(0, 0, map(0,d0_min,d0_max,J0_min,J0_max));
  pwm.setPWM(1, 0, map(90,d1_min,d1_max,J1_min,J1_max));
  pwm.setPWM(2, 0, map(45,d2_min,d2_max,J2_min,J2_max));
  pwm.setPWM(3, 0, map(20,d3_min,d3_max,J3_min,J3_max));
}

// The loop routine runs over and over again forever:
void loop() {
// send data only when you receive data: 
    if (Serial.available() > 0) { 
    // read the incoming 12-digit string: should be configured like "123456789123"
    String incomingString = Serial.readString();

    // parse string into 3-digit pieces and convert each to an integer angle, 
    // e.g. J0=123, J1=456, etc.
    int J0 = incomingString.substring(0,3).toInt();
    int J1 = incomingString.substring(3,6).toInt();
    int J2 = incomingString.substring(6,9).toInt();
    int EE = incomingString.substring(9,12).toInt();

    

    // say what you got:
    Serial.print("J0: "); 
    Serial.println(J0);
    Serial.print("J1: "); 
    Serial.println(J1);
    Serial.print("J2: "); 
    Serial.println(J2);
    Serial.print("EE: "); 
    Serial.println(EE);
    
    // move servos to new positions
    // map figures out where first argument lies between 2nd and 3rd
    // arguments, and interpolates it to the same relative position
    // between 4th and 5th arguments.
    // We use this to convert degrees to servo pulselength for pwm.
    pwm.setPWM(0, 0, map(J0,d0_min,d0_max,J0_min,J0_max));
    pwm.setPWM(1, 0, map(J1,d1_min,d1_max,J1_min,J1_max));
    pwm.setPWM(2, 0, map(J2,d2_min,d2_max,J2_min,J2_max));
    pwm.setPWM(3, 0, map(EE,d3_min,d3_max,J3_min,J3_max));
    }
  

}
