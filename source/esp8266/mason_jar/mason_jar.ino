/*
 * Copyright 2020 Marc SIBERT
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// #define FASTLED_ESP8266_NODEMCU_PIN_ORDER
// #include <FastLED.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "App.h"

static const uint8_t NUM_LEDS = 5;

#include "secrets.h"
static const String ssid(SECRET_SSID);
static const String password(SECRET_PASSWORD);


#if 1
App app( "192.168.1.35" );
#else
App app( "broker.mqttdashboard.com", 8000 );
#endif

// CRGB l1[NUM_LEDS];
// CRGB l2[NUM_LEDS];

void callback(const char* topic, byte* payload, unsigned int length) {
  app.received(topic, payload, length);
}


/**
 * Fonction d'initialisation de l'application
 */
void setup() { 
  Serial.begin(115200);
  delay(1000);
  
  Serial.println(__FILE__);
  Serial.println(__DATE__ "T" __TIME__);
  Serial.println(F("Copyright 2000 - Marc SIBERT"));
  
  Serial.print(F("Connecting to "));
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  
  Serial.println(F("WiFi connected"));
  Serial.print(F("IP address: "));
  Serial.println(WiFi.localIP());

  app.setup();

  
/*
  FastLED.addLeds<NEOPIXEL, 2>(l1, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 1>(l2, NUM_LEDS);
*/  
}

/**
 * Fonction appelée en boucle
 */
void loop() {
  static uint8_t hue = 0; 
  static const uint8_t v = 64;

  app.loop();


/*
  l1[0] = CHSV(hue, 255, v);
  l1[1] = CHSV(32 + hue, 255, v);
  l1[2] = CHSV(64 + hue, 255, v);
  l1[3] = CHSV(96 + hue, 255, v);
  l1[4] = CHSV(128 + hue, 255, v);

  l2[0] = CHSV(16 + hue, 255, v);
  l2[1] = CHSV(16 + 32 + hue, 255, v);
  l2[2] = CHSV(16 + 64 + hue, 255, v);
  l2[3] = CHSV(16 + 96 + hue, 255, v);
  l2[4] = CHSV(16 + 128 + hue++, 255, v);

  FastLED.delay(30);
*/  
}
