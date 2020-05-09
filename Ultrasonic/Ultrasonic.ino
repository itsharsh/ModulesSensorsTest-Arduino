long distance;
int trigpin = 6;
int echopin = 7;
void setup() {
  Serial.begin(9600);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  Serial.println("Hello");
}

void loop()
{
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  distance = pulseIn(echopin, HIGH);
  distance /= 58.2;
  if (distance > 2 && distance < 90)
  {
    Serial.print(" Dist: ");
    Serial.println(distance);
  }
  delay(20);
}
