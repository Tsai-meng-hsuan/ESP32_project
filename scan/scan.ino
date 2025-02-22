#include "WiFi.h"
 
void setup() {
  Serial.begin(115200);
}
  
void loop() {
   scanAP();
   delay(10000);
}
 
void scanAP(void) {
  int n = WiFi.scanNetworks();
  delay(1000);
  Serial.println("scan Wi-Fi done");
  if (n == 0)
    Serial.println("no Wi-Fi networks found");
  else
  {
    Serial.print(n);
    Serial.println(" Wi-Fi networks found");
    for (int i = 0; i < n; ++i)
     {
      Serial.print(i + 1);
      Serial.print(": ");
      //印出SSID
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      //印出RSSI強度
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      //印出加密模式
      Serial.println(WiFi.encryptionType(i),HEX);
      delay(10);
     }
  }
}