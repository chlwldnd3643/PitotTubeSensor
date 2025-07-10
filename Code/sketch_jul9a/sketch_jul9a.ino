#include <Wire.h>
#include "airspeed_utils.h"

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  Wire.beginTransmission(0x28);
  Wire.endTransmission();
  delay(2); // wait for sensor

  Wire.requestFrom(0x28, 4);
  if (Wire.available() >= 4) {
    byte a = Wire.read();
    byte b = Wire.read();
    byte c = Wire.read();
    byte d = Wire.read();

    int raw_pressure = ((a & 0x3F) << 8) | b;

    float delta_p = getDifferentialPressure(raw_pressure);
    float airspeed = calculateAirSpeed(delta_p);

    Serial.print("ΔP: "); Serial.print(delta_p); Serial.print(" Pa, ");
    Serial.print("Speed: "); Serial.print(airspeed); Serial.println(" km/h");
  }

  delay(100);
}
