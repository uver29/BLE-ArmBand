/*
 * The circuit:
 *   ----------------------------
 *   |Arduino Pin | HM-10 Module|
 *   ----------------------------
 *   |     10     |     Tx      |
 *   |     11     |     Rx      |
 *   |     5v     |     VCC     |
 *   |     Gnd    |     Gnd     |
 *   ---------------------------- 
 */

#include <SoftwareSerial.h>
SoftwareSerial HM10Serial(10, 11);

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Serial Monitor Ready!");
  HM10Serial.begin(115200);
}

void loop() {
  if (HM10Serial.available()) {
    Serial.write(HM10Serial.read());
  }
  if (Serial.available()) {
    HM10Serial.write(Serial.read());
  }
}
