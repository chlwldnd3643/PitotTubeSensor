#include <Wire.h>

#define SENSOR_ADDR 0x28  // 보통 0x28 ~ 0x2F 사이. 확인 필요

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  Wire.beginTransmission(SENSOR_ADDR);
  Wire.endTransmission();
  
  Wire.requestFrom(SENSOR_ADDR, 4);  // 4바이트: 상태+압력 2바이트 + 온도 2바이트

  if (Wire.available() == 4) {
    uint8_t msb = Wire.read();
    uint8_t lsb = Wire.read();
    uint8_t temp_msb = Wire.read();
    uint8_t temp_lsb = Wire.read();

    uint16_t pressure_raw = ((msb & 0x3F) << 8) | lsb;
    uint16_t temp_raw = ((temp_msb << 8) | temp_lsb) >> 5;

    // 압력값 변환 (센서 데이터시트 참조, 예: 0x0666 ~ 0x3999 사이)
    float pressure = ((float)pressure_raw - 1638) * (1.0 / (13107)) * (1.0);  // 단위: 차압 (비율)
    float temperature = ((float)temp_raw * 0.0977) - 50.0;

    Serial.print("Pressure (raw): "); Serial.print(pressure_raw);
    Serial.print(" => Pressure (scaled): "); Serial.print(pressure); Serial.println(" (ratio)");
    Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" C");
  }

  delay(100);
}
