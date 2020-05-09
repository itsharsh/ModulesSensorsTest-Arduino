#include<SPI.h>
#include<RF24.h>
#include "printf.h"

//NRF      ARDUINO
//1 GND    GND
//2 VCC    3.3V
//3 CE     9  out
//4 CSN    10  out
//5 SCK    13 out
//6 MOSI   11 out
//7 MISO   12 in

int CE_PIN = 9, CSN_PIN = 10;
RF24 Radio(CE_PIN, CSN_PIN);
const uint64_t pipeOut = 0xB8B8F0F0E1LL;

struct radio
{
  int x;
  int y;
} data;

void setup()
{
  Serial.begin(115200);
  Radio.begin();
  printf_begin();
  Radio.setPALevel(RF24_PA_MAX);
  Radio.setDataRate(RF24_2MBPS);
  Radio.setChannel(110);
  Radio.openWritingPipe(pipeOut);
  Radio.printDetails();
  delay(2000);
  data.x = 1;
  data.y = 2;
}

void loop()
{
  data.x++;
  data.y++;
  Serial.print(data.x);
  unsigned long timeDiff = micros();
  Radio.write(&data, sizeof(data));
  Serial.print("\t");
  Serial.println(timeDiff - micros());
}
