int latchPin = 3; //st_cp
int clockPin = 2; //sh_cp
int dataPin = 4;  //ds

byte leds = 0b00000000;

byte greenHigh[5] = {10, 12, 7, 5, 4};
byte greenLow[5] = {9, 11, 8, 6, 3};
byte redLow[5] = {10, 12, 7, 5, 4};
byte redHigh[5] = {9, 11, 8, 6, 3};

int n;

void setup()
{
  Serial.begin(115200);
  for (int i = 0; i < 14; i++)
    pinMode(i, OUTPUT);
}

void loop()
{
  //  for(int i=0;i<5;i++)
  //  {
  //    glowG(i);
  //    delay(500);
  //    glowR(i);
  //    delay(500);
  //  }


  //  sensorValue = analogRead(A0);
  if (Serial.available())

    n = Serial.parseInt();
  Serial.println(n);
  //  bitSet(leds, n);
  //  updateShiftRegister();
  glowLed();
}
