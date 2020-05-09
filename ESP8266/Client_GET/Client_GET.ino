#include<ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define ssid "itsharsh" 
#define password "password"
#define host "api.thingspeak.com"
#define url "GET /apps/thinghttp/send_request?api_key=1GPCB0EO18QY3FH8M HTTP/1.0"

WiFiClient c;
boolean request = true;

String data;

void setup()
{
  
  delay(1000);
  WiFi.disconnect();
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

void send_request()
{
  if (c.connect(host, 80))
  {
    Serial.println("\n\nConnected to Server");
    c.println(url);
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
    request = true;
  }
}
