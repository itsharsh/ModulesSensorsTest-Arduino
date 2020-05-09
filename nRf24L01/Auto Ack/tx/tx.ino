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

int rec[1] = {5};
float time;
bool go_to_tx_mode = false;
char input[32] = "";
int CE_PIN = 9, CSN_PIN = 10;
RF24 radio(CE_PIN, CSN_PIN);
const uint64_t pipeOut = 0xF1F2F3F4E1LL;

void setup()
{
  Serial.begin(115200);
  radio.begin();
  printf_begin();
  delay(100);
  radio.setAutoAck(true);
  radio.enableAckPayload();
  radio.enableDynamicPayloads();
  radio.stopListening();
  radio.openWritingPipe(pipeOut);
  radio.setRetries(15, 15);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_2MBPS);
  radio.setChannel(110);
  radio.printDetails();
  delay(2000);
  Serial.println("Setup Complete");
}

void loop() {
  if (go_to_tx_mode) {
    if (radio.write(input, sizeof(input)))
    {
      time = micros();
      go_to_tx_mode = false;
      Serial.print( input );
      Serial.println("...tx success");
      if (radio.isAckPayloadAvailable())
      {
        radio.read(rec, sizeof(int));
        Serial.print(micros() - time);
        Serial.print(".......received ack payload is : ");
        Serial.println(rec[0]);
      }
      else
      {
        go_to_tx_mode = false; //doing this completely shuts down the transmitter if an ack payload is not received !!
        Serial.println("status has become false so stop here....");
      }
    }
  }
  if (Serial.available())
  {
    int len = Serial.readBytesUntil('\n', input, 31);
    input[len] = '\0';
    go_to_tx_mode = true;
  }
}
