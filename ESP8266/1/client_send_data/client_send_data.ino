#include<ESP8266WiFi.h>

#define ssid "My ASUS"
#define password "qwertyuiop"

IPAddress ip(52, 7, 7, 190);
WiFiClient cl;

int var = 0;
void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.printf("\nConnecting to %s", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.printf("\nConnected to %s\n", ssid);
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());
}

void loop() {
  var += 5;
  if (cl.connect(ip, 80)) {
    cl.printf("GET https://api.thingspeak.com/update?api_key=9GZW62FNT7HDCWBS&field1=%d\n", var);
    cl.println("HOST: api.thingspeak.com");
    cl.println("Connection: close");
    cl.println();
  }
}
