#include<ESP8266WiFi.h>

#define ssid "itsharsh"
#define password "password"
#define host "api.thingspeak.com"

WiFiClient c;
boolean request = true;
int var = 0;
String data;

void setup()
{
  Serial.begin(115200);
  delay(1000);
  connect_WiFi();
}

void loop()
{
  if (request)
    send_request();
  get_data();
}

void send_request()
{
  if (c.connect(host, 80))
  {
    Serial.println("\n\nConnected to Server");
    c.printf("GET https://api.thingspeak.com/update?api_key=1GJTDKL6U76R5SV0D&field1=%d HTTP/1.1", var);
    c.print("Host: ");
    c.println(host);
    c.println();
    request = false;
  }
  else
    Serial.println("\nFailed to Connect");
}

void get_data()
{
  while (c.available())
  {
    data = c.readString();
    Serial.println(data);
    if (data.toInt() != 0)
      var += 5;
    request = true;
  }
}

void connect_WiFi()
{
  Serial.print("\nConnecting to : ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWiFi Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}
