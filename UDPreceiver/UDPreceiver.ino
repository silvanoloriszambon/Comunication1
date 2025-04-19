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
int hue=32768;
int saturation=255;
int value=255;
 
void setup() {
  // Setup serial port
  pinMode(2,OUTPUT);
  Serial.begin(115200);  
 
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
  for(int i=0;i<5;i++){
    digitalWrite(2,LOW);
    delay(100);
    digitalWrite(2,HIGH);
    delay(100);
  }

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

    if(packetSize==3){
      hue=(int)packet[0] * 300;
      saturation=(int)packet[1];
      value=(int)packet[2];
      
      Serial.print("hue: ");
      Serial.println(hue);
      pixels.fill(pixels.ColorHSV(hue, saturation, value));
      pixels.show();
    }

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