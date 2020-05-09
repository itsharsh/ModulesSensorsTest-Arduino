#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>
#include "web.h"

//#define ssid "itsharsh"
//#define password "hks12345"

#define ssid "NoAccess"
#define password "ucrjiit2017"

ESP8266WebServer server;

IPAddress ip;

void setup() {
  Serial.begin(115200);
  delay(1000);
  //  Serial.print("Flash Size");
  //  Serial.println(ESP.getFlashChipSize());
  WiFi.begin(ssid, password);
  Serial.printf("\nConnecting to %s", ssid);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.printf("\nConnected to %s\n", ssid);
  Serial.print("IP Address : ");
  Serial.print(WiFi.localIP());

  server.on("/", []() {
    String s = MAIN_page;
    server.send(200, "text/html", s);
  });
  server.on("/data", []() {
    String name1 = server.arg("name");
    String mob = server.arg("number");
    server.send(204, "");
    Serial.print(name1);
    Serial.print("\t");
    Serial.println(mob);
  });
  server.begin();
}

void loop() {
  server.handleClient();
}

void homep() {
  String s = MAIN_page;
  server.send(200, "text/html", s);
}

void rdata() {
}
