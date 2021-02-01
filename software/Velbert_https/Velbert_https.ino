#include <ESP8266WiFi.h>
#include "VelbertMuellParser.h"
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
// By default 'pool.ntp.org' is used with 60 seconds update interval and
// no offset
//NTPClient timeClient(ntpUDP);

// You can specify the time server pool and the offset, (in seconds)
// additionaly you can specify the update interval (in milliseconds).
NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600, 60000);

#define DayInSeconds 86400

VelbertMuellParser  RMP("https://service.tbv-velbert.de/abfall/abfallabfuhr-suche/?tx_tbvabfall_strassensuche%5Baction%5D=list&tx_tbvabfall_strassensuche%5Bcontroller%5D=Abfalldaten&cHash=d222639c1d038b059e8c2d98d1332c00");


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
  
 
  WiFi.begin(ssid,pass);
  Serial.print("checking wifi ");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
    
  Serial.print("\nConnected, IP address: ");
  Serial.println(WiFi.localIP());

  RMP.SetStreet(street);
}

void loop()
{
  int blue;
  pixels.clear();
  timeClient.update();
  setTime(timeClient.getEpochTime()+1*DayInSeconds);
  Serial.print("date: ");
  Serial.print(day());
  Serial.print(".");
  Serial.print(month());
  Serial.print(".");
  Serial.println(year());
  Serial.print("Time: ");
  Serial.println(timeClient.getFormattedTime());
  if(year()>1971){
    if(RMP.CheckDate("Restmüll", day(),month(),year())){
      Serial.println("Heute Graue Tonne!");
      pixels.setPixelColor(2, pixels.Color(15, 15, 15));
      pixels.setPixelColor(3, pixels.Color(15, 15, 15));
    }
    if(RMP.CheckDate("Gelbe", day(),month(),year())){
      Serial.println("Heute Gelb Tonne!");
      pixels.setPixelColor(1, pixels.Color(50, 25, 0));
      pixels.setPixelColor(4, pixels.Color(50, 25, 0));
    }
    if(RMP.CheckDate("Papier-Tonne", day(),month(),year())){
      Serial.println("Heute Blau Tonne!");
      pixels.setPixelColor(0, pixels.Color(0, 0, 50));
      pixels.setPixelColor(5, pixels.Color(0, 0, 50));
      blue = 50;
    }
    else blue = 0;
    for(int ia=0; ia<30;ia++){
      for(int a=0; a<50;a++){
        for(int i=0; i <15;i++){
          pixels.setPixelColor(5, pixels.Color(0, i, blue));
          delay(70);
          pixels.show();
        }
        for(int i=0; i <15;i++){
          pixels.setPixelColor(5, pixels.Color(0, 14-i, blue));
          delay(70);
          pixels.show();
        }
      }
    }
    //      delay(300000);
  }
  else{
        for(int a=0; a<50;a++){
      for(int i=0; i <15;i++){
        pixels.setPixelColor(5, pixels.Color(i, 0, blue));
        delay(70);
        pixels.show();
      }
      for(int i=0; i <15;i++){
        pixels.setPixelColor(5, pixels.Color(14-i, 0, blue));
        delay(70);
        pixels.show();
      }
    }
  }
}
