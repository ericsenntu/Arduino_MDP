#include "DualVNH5019MotorShield.h"

DualVNH5019MotorShield md;

void stopIfFault()
{
  if (md.getM1Fault())
  {
    Serial.println("M1 fault");
    while(1);
  }
  if (md.getM2Fault())
  {
    Serial.println("M2 fault");
    while(1);
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Dual VNH5019 Motor Shield");
  md.init();
  pinMode(3,INPUT);
}

float calc_rpm(float pulse) {
  float rpm = (562.25 * 2 * pulse)/1000000;
  rpm = 60/rpm;
  return rpm;
}

int done = 0;
void loop()
{ int i;
  delay(1000);
  if (done <= 3) {
    int initial_speed = 300;
    int final_speed = 250;
    md.setM1Speed(initial_speed); 
    md.setM2Speed(initial_speed);
    Serial.println("speed 300!!");
    for (i=0; i<100; i++) {
      delay(5);
      Serial.println(calc_rpm(pulseIn(3,HIGH)));
    }
    md.setM2Speed(final_speed);
    md.setM1Speed(final_speed);
    Serial.println("speed 250");
    for (i=0; i<100; i++) {
      delay(5);
      Serial.println(calc_rpm(pulseIn(3,HIGH)));
    }
  }

  done++;
}
