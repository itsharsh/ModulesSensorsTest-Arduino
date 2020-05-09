void setup()
{
  Serial.begin(115200);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);

}
int pir_pin = A5;
void loop()
{
  int data = digitalRead(pir_pin);
  Serial.println(data);
  if (data == HIGH)
    analogWrite(3, 170);
  else
    analogWrite(3, 0);
}
