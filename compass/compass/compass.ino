#include<EngduinoMagnetometer.h>
#include<EngduinoLEDs.h>
#include<Wire.h>

float maxX = 0;
float minX = -1234;
float maxY = 659;
float minY = 0;
float maxZ = 545;
float minZ = 0;

void calib(float magField[3]) {
  if(magField[0]>maxX) {
    maxX = magField[0];
  }
  if (magField[0] < minX) {
    minX = magField[0];
  }

  if (magField[1] > maxY) {
    maxY = magField[1];
  }
  if (magField[1] < minY) {
    minY = magField[1];
  }

  if (magField[2] > maxZ) {
    maxZ = magField[2];
  }
  if (magField[2] < minZ) {
    minZ = magField[2];
  }
}

void setup() {
  // put your setup code here, to run once:
  EngduinoMagnetometer.begin();
  EngduinoLEDs.begin();
}

float magField[3];

float x,y,z,angle;

void compassLight(float ang) {
  //which light to light.
  int d;

  EngduinoLEDs.setAll(OFF);
  if(ang >= 0 && ang < 22.5) {
    d=7; }
  else if (ang >= 22.5 && ang < 45) {
    d=6; }
  else if (ang >= 45 && ang < 67.5) {
    d=5;
  }
  else if (ang >= 67.5 && ang < 90) {
    d=4;
  }
  else if (ang >= 90 && ang < 112.5) {
    d=3;
  }
  else if (ang >= 112.5 && ang < 135) {
    d=2;
  }
  else if (ang >= 135 && ang < 157.5) {
    d=1;
  }
  else if (ang >= 157.5 && ang < 180) {
    d=0;
  }
  else if (ang >= 180 && ang < 202.5) {
    d=15;
  }
  else if (ang >= 202.5 && ang < 225) {
    d=14;
  }
  else if (ang >= 225 && ang < 247.5) {
    d=13;
  }
  else if (ang >= 247.5 && ang < 270) {
    d=12;
  }
  else if (ang >= 270 && ang < 292.5) {
    d=11;
  }
  else if (ang >= 292.5 && ang < 315) {
    d=10;
  }
  else if (ang >= 315 && ang < 337.5) {
    d=9;
  }
  else if (ang >= 337.5 && ang < 360) {
    d=8;
  }
  Serial.print("d: ");
  Serial.println(d);
  EngduinoLEDs.setLED(d,GREEN);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Let's get mag field readings.
  EngduinoMagnetometer.xyz(magField);
  x = magField[0];
  y = magField[1];
  z = magField[2];

  //calib
  float rangeX = maxX - minX;
  float rangeY = maxY - minY;
  float rangeZ = maxZ - minZ;

  x = x / rangeX;
  y = y / rangeY;
  z = z / rangeZ;

  x = 0 - x;
  y = 0 - y;
  
  // convert to heading.
  angle = atan2(y,x);
  angle = angle * 180 / PI;
  if (angle < 0) {
    angle = 360 + angle;
  }

  Serial.print(x);
  Serial.print(", ");
  Serial.print(y);
  Serial.print(", ");
  Serial.println(z);
  Serial.print("Angle: ");
  Serial.println(angle); 
  
  compassLight(angle);
  calib(magField);
  delay(100);
}
