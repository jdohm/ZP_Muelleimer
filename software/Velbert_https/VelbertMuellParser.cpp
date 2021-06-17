/*
    VelbertMuellParser.cpp - Library to parse the Trash website of the German city Velbert.
    This will be used to evaluate if tomorrow the trash will be emptied. 
    So that we can signal to put out the trash.
    Created by Jannis Dohm, 2020-04-20.
    Released under MIT License.
*/

#include "Arduino.h"
#include "VelbertMuellParser.h"
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

//_DatabaseURL = "https://service.tbv-velbert.de/abfall/abfallabfuhr-suche/?tx_tbvabfall_strassensuche%5Baction%5D=list&tx_tbvabfall_strassensuche%5Bcontroller%5D=Abfalldaten&cHash=d222639c1d038b059e8c2d98d1332c00";

VelbertMuellParser::VelbertMuellParser(char *DatabaseURL){//the URL needs to be checked on the official website "https://abfallkalenderVelbert.insert-infotech.de/index.php"
    _DatabaseURL =  DatabaseURL;
}

void VelbertMuellParser::SetStreet(String Street){//Enter your Streetname
  _Street = Street;
//  return 0;
}

bool VelbertMuellParser::CheckDate(char* SearchFor, int day, int month, int year){
    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    client->setInsecure();
    HTTPClient https;

    String postData = "tx_tbvabfall_strassensuche%5B__referrer%5D%5B%40extension%5D=Tbvabfall&tx_tbvabfall_strassensuche%5B__referrer%5D%5B%40vendor%5D=EveryConsult&tx_tbvabfall_strassensuche%5B__referrer%5D%5B%40controller%5D=Abfalldaten&tx_tbvabfall_strassensuche%5B__referrer%5D%5B%40action%5D=list&tx_tbvabfall_strassensuche%5B__referrer%5D%5Barguments%5D=YTo0OntzOjY6ImFjdGlvbiI7czo0OiJsaXN0IjtzOjEwOiJjb250cm9sbGVyIjtzOjExOiJBYmZhbGxkYXRlbiI7czoxMToiYWJnZXNjaGlja3QiO3M6MToiMSI7czoxMToic3VjaGJlZ3JpZmYiO3M6MTI6IkhhdXB0c3RyYcOfZSI7fQ%3D%3Dd6c50c9284915c804ecfe2866784057e0ee2985c&tx_tbvabfall_strassensuche%5B__referrer%5D%5B%40request%5D=a%3A4%3A%7Bs%3A10%3A%22%40extension%22%3Bs%3A9%3A%22Tbvabfall%22%3Bs%3A11%3A%22%40controller%22%3Bs%3A11%3A%22Abfalldaten%22%3Bs%3A7%3A%22%40action%22%3Bs%3A4%3A%22list%22%3Bs%3A7%3A%22%40vendor%22%3Bs%3A12%3A%22EveryConsult%22%3B%7D1b4dce7c057e7503073a6937f97eee8e8b7650e3&tx_tbvabfall_strassensuche%5B__trustedProperties%5D=a%3A2%3A%7Bs%3A11%3A%22abgeschickt%22%3Bi%3A1%3Bs%3A11%3A%22suchbegriff%22%3Bi%3A1%3B%7Dae8a10e23f532f6ce1dd43681b3c3b0c393dedc7&tx_tbvabfall_strassensuche%5Babgeschickt%5D=1&tx_tbvabfall_strassensuche%5Bsuchbegriff%5D=" + _Street;

//    Serial.println("postData: ");
//    Serial.println(postData);
  if (https.begin(*client, String(_DatabaseURL))) {  // HTTPS
    Serial.println("[HTTPS] POST...");
    //https.addHeader("Content-Type", "text/plain");
    https.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode = https.POST(postData);

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTPS] POST... code: %d\n", httpCode);
      // file found at server?
    if (httpCode == HTTP_CODE_OK) {
        int payload = https.getSize();
        Serial.println(String("[HTTPS] Received payload: ") + payload);
        Stream *httpsS = https.getStreamPtr();
        while(httpsS -> available()){

//        String line = httpsS -> readStringUntil('\n');
//        Serial.println(line);

        String line;
        if(httpsS -> find(SearchFor)){
            Serial.print("found ");
            Serial.println(SearchFor);
        }
        for(int i=0; i<3;i++){
          line = httpsS -> readStringUntil('\n');
          Serial.print(" looking for ");
          String _SDate = _ToTwoString(day) + "." + _ToTwoString(month) + "." + year;
          Serial.print(_SDate);
          Serial.println(" in the following line:");
          Serial.println(line);
          if(1 <= line.indexOf(_SDate)) {
            Serial.println("found it!");
            return true;
          }
        }
        Serial.println("not found!");
        return false;
        }
    }
    } else {
    Serial.printf("[HTTPS] POST... failed, error: %s\n\r", https.errorToString(httpCode).c_str());
    }

    https.end();
  } else {
    Serial.printf("[HTTPS] Unable to connect\n\r");
  }
  return false;
}

String VelbertMuellParser::_ToTwoString(int Num){
    if(Num<0) return "00";
    if(Num<10) return "0" + String(Num);
    return String(Num);
}
