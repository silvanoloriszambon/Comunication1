#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_NeoPixel.h>
 
// Set WiFi credentials
#define WIFI_SSID "MegaWiFi_2"
#define WIFI_PASS "mega1234"
#define UDP_PORT 4210
#define PIN        5
#define NUMPIXELS  7

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// UDP
WiFiUDP UDP;
char packet[255];
char reply[] = "Packet received!";
 
void setup() {
  // Setup serial port
  Serial.begin(115200);
  Serial.println("CIAO MONDO");
 
  // Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
 
  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  // Loop continuously while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
 
  // Connected to WiFi
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  // Begin listening to UDP port
  UDP.begin(UDP_PORT);
  Serial.print("Listening on UDP port ");
  Serial.println(UDP_PORT);
  pixels.begin();
 
}

void loop() {

  // If packet received...
  int packetSize = UDP.parsePacket();
  if (packetSize) {
    Serial.print("Received packet! Size: ");
    Serial.println(packetSize); 
    int len = UDP.read(packet, 255);
    if (len > 0)
    {
      packet[len] = '\0';
    }
    Serial.print("Packet received: ");
    Serial.println(packet);

    if(packetSize == 2){
      pixels.fill(pixels.Color(250, 250, 250));
      pixels.show();   
    }

    if(packetSize == 1){
      pixels.fill(pixels.Color(0, 0, 0));
      pixels.show();   
    }
  }

}