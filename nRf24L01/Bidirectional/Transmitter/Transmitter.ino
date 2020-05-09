#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
int msg[1] = {1};
int rec[1] = {5};
bool stat = true;
RF24 radio(9, 10);
const uint64_t pipe[1] = {0xF0F0F0F0E1LL};

void setup()
{
  Serial.begin(115200);
  radio.begin();
  delay(1000);
  radio.setAutoAck(true);
  radio.enableAckPayload();
  radio.enableDynamicPayloads();
  radio.openWritingPipe(pipe[0]);
  radio.setRetries(15, 15);
}
char str[]="ABCDEFG";
void loop()
{
  if (stat)
  {
    radio.stopListening();
    if (radio.write(msg, sizeof(msg)))
    {
      Serial.print( msg[0] );
      Serial.print("  transmitted successfully !!  ");
      if (radio.isAckPayloadAvailable())
      {
        radio.read(str, sizeof(str));
        Serial.print("received ack payload is : ");
        Serial.print(str);
      }
      else
      {
        stat = false; //doing this completely shuts down the transmitter if an ack payload is not received !!
        Serial.println("status has become false so stop here....");
      }
      Serial.println();
      msg[0] += 3;;
      if (msg[0] >= 100)
      {
        msg[0] = 1;
      }
    }
    else
    {
      Serial.println("failed tx...");
    }
  }
}
