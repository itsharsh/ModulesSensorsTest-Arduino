//NRF      ARDUINO
//1 GND    GND
//2 VCC    3.3V
//3 CE     9  out
//4 CSN    10  out
//5 SCK    13 out
//6 MOSI   11 out
//7 MISO   12 in

#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
#include "printf.h"

int CE_PIN = 9, CSN_PIN = 10;
RF24 radio(CE_PIN, CSN_PIN);
int rec[1] = {2};
char red[32];
const uint64_t pipeIn = 0xF1F2F3F4E1LL;

void setup()
{
  Serial.begin(115200);
  radio.begin();
  printf_begin();
  delay(100);
  radio.setAutoAck(true);
  radio.enableAckPayload();
  radio.enableDynamicPayloads();
  radio.openReadingPipe(1, pipeIn);
  radio.setRetries(15, 15);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_2MBPS);
  radio.setChannel(110);
  radio.openReadingPipe(0, pipeIn);
  radio.startListening();
  radio.printDetails();
  delay(2000);
  Serial.println("Setup Complete");
}
void loop() {
  if ( radio.available() ) {
    radio.writeAckPayload( 1, rec, sizeof(int) );
    radio.read( red, sizeof(red) );
    rec[0] += 2;
    Serial.print("character got is : ");
    Serial.println(red);
  }
}
