#include<ESP8266WiFi.h>

char* ssid = "Vibes";
char* pwd = "HappyBirthday";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Connection to WiFi...");
  WiFi.begin(ssid, pwd);
  delay(10000);
  server.begin();
  IPAddress ip = WiFi.localIP();
  Serial.println("IP Address : ");
  Serial.print(ip);Serial.println();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client");
    boolean clib = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n' && clib) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println("Refresh: 5"); 
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head><title>ESP8266 WebServer</title></head>");
          client.println("<body background=\"https://s-media-cache-ak0.pinimg.com/originals/af/6b/91/af6b9186a74c9c5af1d8d111ceea41c5.jpg\">");
          client.print("Timing is : ");
          client.println((long)millis());
          client.println("</body>");
          client.println("</html>");
        }
        if (c == '\n') {
          clib = true;
        } else if (c != '\r') {
          clib = false;
        }
      }
    }
    delay(1);
    client.stop();
    Serial.println("Client disconnected");
  }
}
