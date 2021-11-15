#include <OneButton.h>
OneButton button(2);

/* 
  Basic test program, send date at the BAND you seted.
  
  by Aaron.Lee from HelTec AutoMation, ChengDu, China
  成都惠利特自动化科技有限公司
  www.heltec.cn
  
  this project also realess in GitHub:
  https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series
*/
#include "heltec.h"
#define BAND    915E6  //you can set band here directly,e.g. 868E6,915E6

int counter = 0;
int buttonState;

unsigned long timePress = 0;
unsigned long timePressLimit = 0;
int clicks = 0;

void setup() {
  
  //WIFI Kit series V1 not support Vext control
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  button.attachDoubleClick(doubleclick);
  button.attachClick(click1);
  
}

void sender1(){
  Serial.print("Sending packet: ");
    Serial.println(counter);
  // send packet
    LoRa.beginPacket();
/*
* LoRa.setTxPower(txPower,RFOUT_pin);
* txPower -- 0 ~ 20
* RFOUT_pin could be RF_PACONFIG_PASELECT_PABOOST or RF_PACONFIG_PASELECT_RFO
*   - RF_PACONFIG_PASELECT_PABOOST -- LoRa single output via PABOOST, maximum output 20dBm
*   - RF_PACONFIG_PASELECT_RFO     -- LoRa single output via RFO_HF / RFO_LF, maximum output 14dBm
*/
    LoRa.setTxPower(14,RF_PACONFIG_PASELECT_PABOOST);
    LoRa.print("hello  hello ");
    LoRa.print(counter);
    LoRa.endPacket();
  
    counter++;
    digitalWrite(25, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(25, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);                       // wait for a second
  
}

void sender2(){
  Serial.print("Sending packet: ");
    Serial.println(counter);
  // send packet
    LoRa.beginPacket();
/*
* LoRa.setTxPower(txPower,RFOUT_pin);
* txPower -- 0 ~ 20
* RFOUT_pin could be RF_PACONFIG_PASELECT_PABOOST or RF_PACONFIG_PASELECT_RFO
*   - RF_PACONFIG_PASELECT_PABOOST -- LoRa single output via PABOOST, maximum output 20dBm
*   - RF_PACONFIG_PASELECT_RFO     -- LoRa single output via RFO_HF / RFO_LF, maximum output 14dBm
*/
    LoRa.setTxPower(14,RF_PACONFIG_PASELECT_PABOOST);
    LoRa.print("hello  hello ");
    LoRa.print(counter);
    LoRa.endPacket();
  
    counter++;
    digitalWrite(25, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(2000);                       // wait for a second
    digitalWrite(25, LOW);    // turn the LED off by making the voltage LOW
    delay(2000);                       // wait for a second
}
void click1() {
  
  sender1();
  }

void doubleclick() {
  
  sender2();
  }

void loop() {
    // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");
    digitalWrite(25, HIGH);
    delay(1000);                       // wait for a second
    digitalWrite(25, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);                       // wait for a second

    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }
    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }

    button.tick();
    button.tick();
    



} 
