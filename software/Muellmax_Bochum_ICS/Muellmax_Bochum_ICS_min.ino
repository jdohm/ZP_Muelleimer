#include <ESP8266WiFi.h>
#include <ICSParser.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Time.h>

#include "secrets.h"

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN       4
#define NUMPIXELS 6

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

WiFiUDP ntpUDP;

// You can specify the time server pool and the offset, (in seconds)
// additionaly you can specify the update interval (in milliseconds).
NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600, 60000);

#define DayInSeconds 86400

ICSParser  ICSParsery("bochum.ics");

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
pixels.begin();
pinMode(LED_BUILTIN, OUTPUT);
digitalWrite(LED_BUILTIN, HIGH);

  
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println();
  timeClient.begin();
  
 
  //ssid und pass sind in der secrets.h gespeichert, da diese geheimgehalten werden müssen!
  WiFi.begin(ssid,pass);
  Serial.print("checking wifi ");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
    
  Serial.print("\nConnected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  pixels.clear();
  timeClient.update();
  setTime(timeClient.getEpochTime()+DayInSeconds);
  Serial.print("date: ");
  Serial.print(day());
  Serial.print(".");
  Serial.print(month());
  Serial.print(".");
  Serial.println(year());
  Serial.print("Time: ");
  Serial.println(timeClient.getFormattedTime());

  if(ICSParsery.CheckDate("Grau", day(),month(),year())){
    Serial.println("Heute Graue Tonne!");
    pixels.setPixelColor(2, pixels.Color(15, 15, 15));
    pixels.setPixelColor(3, pixels.Color(15, 15, 15));
  }
  if(ICSParsery.CheckDate("Gelb", day(),month(),year())){
    Serial.println("Heute Gelb Tonne!");
    pixels.setPixelColor(1, pixels.Color(50, 25, 0));
    pixels.setPixelColor(4, pixels.Color(50, 25, 0));
  }
  if(ICSParsery.CheckDate("Blau", day(),month(),year())){
    Serial.println("Heute Blau Tonne!");
    pixels.setPixelColor(0, pixels.Color(0, 0, 50));
    pixels.setPixelColor(5, pixels.Color(0, 0, 50));
  }
}
