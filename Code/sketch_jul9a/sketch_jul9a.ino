#include <Wire.h>

#define SENSOR_ADDR 0x28  // 센서 I2C 주소 (확인 필요)

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  Wire.beginTransmission(SENSOR_ADDR);
  Wire.endTransmission();
  
  Wire.requestFrom(SENSOR_ADDR, 4);  // 4바이트 요청

  if (Wire.available() == 4) {
    uint8_t msb = Wire.read();
    uint8_t lsb = Wire.read();
    Wire.read();  // 온도 MSB (무시)
    Wire.read();  // 온도 LSB (무시)

    uint16_t pressure_raw = ((msb & 0x3F) << 8) | lsb;

    // 압력 비율 (0.0 ~ 1.0)
    float pressure_ratio = ((float)pressure_raw - 1638) / (14745 - 1638);

    // 압력 환산 (예: ±1 psi 센서 → ±6.894 kPa)
    float pressure_kPa = (pressure_ratio * 2.0 - 1.0) * 6.894;

    Serial.print("Pressure (raw): "); Serial.print(pressure_raw);
    Serial.print(" => Pressure: "); Serial.print(pressure_kPa); Serial.println(" kPa");
  }

  delay(100);
}
