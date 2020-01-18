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

#include <ESP8266WiFi.h>
#include "App.h"

static const uint8_t NUM_LEDS = 5;

#include "secrets.h"
static const String ssid(SECRET_SSID);
static const String password(SECRET_PASSWORD);


// App app( "192.168.1.2" );

CRGB l1[16];
// CRGB l2[NUM_LEDS];

void callback(const char* topic, byte* payload, unsigned int length) {
//  app.received(topic, payload, length);
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

#if 0  
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
#endif
  

  FastLED.addLeds<NEOPIXEL, 1>(l1, 16);
/*
  FastLED.addLeds<NEOPIXEL, 1>(l2, NUM_LEDS);
*/  
}

/**
 * Fonction appelée en boucle
 */
void loop() {
  static uint8_t hue = 0; 
  static const uint8_t v = 64;

//  app.loop();

  for (int i = 0; i < 4; ++i) 
    for (int j = 0; j < 4; ++j) 
      l1[i * 4 + j] = CHSV((hue + int(round(50*sqrt((i-1.5)*(i-1.5)+(j-1.5)*(j-1.5))))) % 256, 255, v);

  hue += 1;
  FastLED.delay(10);
}
