#include <SoftwareSerial.h>

SoftwareSerial BLE1(1, 2);  //RX, TX
SoftwareSerial BLE2(3, 4);  //RX, TX


void setup() {

  pinMode(0, OUTPUT);
  
  BLE1.begin(115200);  
  delay(100);
  
  setupBLE1();

  BLE2.begin(115200);
  delay(100);

  setupBLE2();

  BLE2.begin(115200);
}

void loop() {

  scan();
}

void setupBLE1() {
  // the value of delay used in this function is more than what is necessary
  // so that there is no problem in initialising the HM 10
  BLE1.println("AT");
  delay(200);
  
  BLE1.println("AT+RENEW");
  delay(200);

  delay(100);
  BLE1.println("AT+RESET");
  delay(200);
  
  BLE1.println("AT");
  delay(200);
  
  BLE1.println("AT+IBE0D00DC100");  // uuid setup
  delay(200);
  
  BLE1.println("AT+IBE1C59E4B37");  // uuid setup
  delay(200);
  
  BLE1.println("AT+IBE29232493F");  // uuid setup
  delay(200);
  
  BLE1.println("AT+IBE35275A66B");  // uuid setup
  delay(200);
  
  BLE1.println("AT+MARJ0x0002");  // Major no = 2 (for 2m reference)
  delay(200);
  
  BLE1.println("AT+MINO0x0001");  // Minor no = 1
  delay(200);
  
  BLE1.println("AT+ADVI0");  // advertising interval = 100ms
  delay(200);
  
  BLE1.println("AT+NAMEarmBand");  // iBeacon name = armBand
  delay(200);
  BLE1.println("AT+ADTY3");  // Advertising  only
  delay(200);
  
  BLE1.println("AT+IBEA1");  // iBeacon mode enabled
  delay(200);
  
  BLE1.println("AT+DELO2");  //Broadcast only (saves power)
  delay(200);
  
  BLE1.println("AT+PWRM0");  // Sleep mode enabled
  delay(200);
  
  BLE1.println("AT+RESET");
  delay(200);
}

//vibrate the motor for 10 seconds
void vibrate() {
  digitalWrite(0, HIGH);
  delay(10000);
  digitalWrite(0, LOW);
}

void setupBLE2() {
  
  BLE2.println("AT");
  delay(200);
  
  BLE2.println("AT+RENEW");
  delay(200);
  
  BLE2.println("AT+RESET");
  delay(200);
  
  BLE2.println("AT+IMME1");
  delay(200);
  
  BLE2.println("AT+ROLE1");
  delay(200);
  
  BLE2.println("AT+RESET");
  delay(200);
  
  BLE2.println("AT+SCAN1");
  delay(200);
  
  BLE2.println("AT+RESET");
  delay(200);
  
}


void scan() {
  unsigned long t;
  delay(100);
  String scan_result = "";
  BLE2.println("AT+DISI?");
  t = millis();
  while((millis()-t)<2000)
  {
    if(BLE2.available())
    {
      scan_result.concat(char(BLE2.read()));
    }
  }
  int i = 59;
  while(i < scan_result.length()) {
    if(scan_result.substring(i-32, i) == "D00DC100C59E4B379232493F5275A66B" && scan_result.substring(i+5, i+9) != "0001") {
      vibrate();
    }
    i += 80;
  }
}
