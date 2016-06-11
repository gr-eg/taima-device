#include <Wire.h>

const int xPin = A2;
const int yPin = A1;
const int zPin = A0;

int minVal = 330.00;
int maxVal = 440.00;
String oldPosition = "";

void setup() {
  Serial.begin(9600);
}

void loop() {
  float xRead = map_to_decimal(analogRead(xPin));
  float yRead = map_to_decimal(analogRead(yPin));
  float zRead = map_to_decimal(analogRead(zPin));

  String newPosition = oldPosition;

  if(xRead == 0 && yRead == 0 && zRead == 1) {
    newPosition = "A";
  }
  else if(xRead == -1 && yRead == 0 && zRead == 0) {
    newPosition = "B";
  }
  else if(xRead == 0 && yRead == 1 && zRead == 0) {
    newPosition = "C";
  }
  else if(xRead == 1 && yRead == 0 && zRead == 0) {
    newPosition = "D";
  }
  else if(xRead == 0 && yRead == -1 && zRead == 0) {
    newPosition = "E";
  }
  else if(xRead == 0 && yRead == 0 && zRead == -1) {
    newPosition = "F";
  }

  if(newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println("position_changed('" + newPosition + "')");
  }

  delay(500);
}

float calculate_difference(float before, float after) {
  return fabs(before - after);
}

float map_to_decimal(int input) {
  float val = mapfloat(input, minVal, maxVal, 0.0, 1.0);
  return round(val * 2.0) / 2.0; // Round to the nearest half
}

float mapfloat(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}
