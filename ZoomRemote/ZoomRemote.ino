/**
   BasicHTTPClient.ino

    Created on: 24.05.2015

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;

const int mute = 13;
const int camera = 12;
const int hangup = 14;

void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);
  Serial.println("Starting...");
  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("robotcheese", "monkeybuttt");

  pinMode(mute, INPUT_PULLUP);
  pinMode(camera, INPUT_PULLUP);
  pinMode(hangup, INPUT_PULLUP);
}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    int isMute = digitalRead(mute);
    int isCamera = digitalRead(camera);
    int isHang = digitalRead(hangup);
    if (isMute == 0) {
      WiFiClient client;
      HTTPClient http;

      Serial.print("[HTTP] begin...\n");
      if (http.begin(client, "http://192.168.1.175:3000/aud")) {  // HTTP
        Serial.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if (httpCode > 0) {
          // HTTP header has been send and Server response header has been handled
          Serial.printf("[HTTP] GET... code: %d\n", httpCode);

          // file found at server
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String payload = http.getString();
           Serial.println(payload);
          }
        } else {
          Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
     delay(200);
    }
    
    if (isCamera == 0) {
      WiFiClient client;
      HTTPClient http;

      Serial.print("[HTTP] begin...\n");
      if (http.begin(client, "http://192.168.1.175:3000/cam")) {  // HTTP
        Serial.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if (httpCode > 0) {
          // HTTP header has been send and Server response header has been handled
          Serial.printf("[HTTP] GET... code: %d\n", httpCode);

          // file found at server
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String payload = http.getString();
           Serial.println(payload);
          }
        } else {
          Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
    delay(200);
  }
    
    
  if (isHang == 0) {
      WiFiClient client;
      HTTPClient http;
      Serial.print("[HTTP] begin...\n");
      if (http.begin(client, "http://192.168.1.175:3000/hang")) {  // HTTP
        Serial.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if (httpCode > 0) {
          // HTTP header has been send and Server response header has been handled
          Serial.printf("[HTTP] GET... code: %d\n", httpCode);

          // file found at server
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String payload = http.getString();
           Serial.println(payload);
          }
        } else {
          Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }
    delay(200);
  }
  delay(1);
}
