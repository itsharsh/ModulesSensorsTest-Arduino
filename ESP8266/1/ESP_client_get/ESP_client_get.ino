#include<ESP8266WiFi.h>
#include<String.h>
char *ssid = "itsharsh";
char *pwd = "hks12345";
char *host = "Host: api.thingspeak.com";
char *url = "GET /apps/thinghttp/send_request?api_key=C93JI290R5HYE1ZL HTTP/1.0";
String line[50];
boolean chk = true;

IPAddress hostip(52, 7, 7, 190);
WiFiClient client;
int l = 0;

void setup()
{
  Serial.begin(115200);
  delay(2000);
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, pwd);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Connected");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
}

void loop()
{
  l = 0;
  while (client.connected())
  {
    if (client.available())
    {
      line[l] = client.readStringUntil('\n');
      Serial.println(line[l++]);
      chk = true;
    }
  }
  if (chk)
  {
    sendrequest();
    chk = false;
  }
}

void sendrequest()
{
  client.stop();
  if (client.connect(hostip, 80))
  {
    Serial.println("\n\nConnected to Server");
    client.println(url);
    client.println(host);
    client.println("Connection: close");
    client.println();
  }
  else
  {
    Serial.println("Failed to Connect");
  }
}

