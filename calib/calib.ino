#include<EngduinoMagnetometer.h>
#include<Wire.h>

void setup() {
  // put your setup code here, to run once:
  EngduinoMagnetometer.begin();
}

float maxX,minX,maxY,minY,maxZ,minZ;
float magField[3];

void loop() {
  // put your main code here, to run repeatedly:
  EngduinoMagnetometer.xyz(magField);
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

  Serial.print("Max X: ");
  Serial.print(maxX);
  Serial.print(", ");
  Serial.print("Min X: ");
  Serial.print(minX);
  Serial.println();

  Serial.print("Max Y: ");
  Serial.print(maxY);
  Serial.print(", ");
  Serial.print("Min Y: ");
  Serial.println(minY);

  Serial.print("Max Z: ");
  Serial.print(maxZ);
  Serial.print(", ");
  Serial.print("Min Z: ");
  Serial.println(minZ);
}
