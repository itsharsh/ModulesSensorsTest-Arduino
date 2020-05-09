void updateShiftRegister()
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
}

void glowLed()
{
  for (int i = 0; i <= 8; i++)
  {
    leds = 1 << i;
    updateShiftRegister();
    delay(1000);
  }
  for (int j = 0; j < 8; j++)
  {

    byte myByte = B10000000;
    leds = myByte >> j;
    updateShiftRegister();
    delay(1000);
  }
}

void glowG(byte pin)
{
  digitalWrite(greenHigh[pin], HIGH);
  digitalWrite(greenLow[pin], LOW);
}

void glowR(byte pin)
{
  digitalWrite(redHigh[pin], HIGH);
  digitalWrite(redLow[pin], LOW);
}


