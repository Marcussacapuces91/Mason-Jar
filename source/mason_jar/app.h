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

#pragma once

#include <list>
#include <ArduinoJson.h>

void callback(const char*, byte*, unsigned int);

class App {
public:
  App(const char* aAdresse, const unsigned aPort = 1883) :
    adresse(aAdresse),
    port(aPort),
    nom(String(F("mj-")) + WiFi.macAddress()),
    wifi(),
    mqtt(wifi)
  {}

  void setup() {
    mqtt.setServer(adresse.c_str(), port);
    mqtt.setCallback(callback);
  }

  void loop() {
    if ( !mqtt.connected() ) {
      connect();
    }

    if (!commands.empty()) {
      StaticJsonDocument<200> doc;
      
      const auto& msg = commands.front();
#if 0
      Serial.print("Receive: ");
      Serial.print(msg.first);
      Serial.print(" => ");
      Serial.println(msg.second);
#endif      
      const auto error = deserializeJson(doc, msg.second.c_str());
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
      } else {
        const char* const verb( doc["verb"] );
        if (verb) {
          Serial.print("Verb:");
          Serial.println(verb);
        }
      }
      commands.pop_front();
    }
    
    mqtt.loop();  
  }

  void received(const char* topic, byte* payload, unsigned int length) {
    const std::pair<String, String> msg(std::make_pair( String(topic), String((char*)payload).substring(0, length) ));
    commands.push_back( msg );
  }

protected:
  boolean connect() {
    const String hello( F("mason-jar/hello") );
    const String will( nom + F(" disconnected!") );
    
    if (!mqtt.connect(nom.c_str(), "marc", "", hello.c_str(), 0, false, will.c_str())) {
      Serial.print(F("Connexion impossible ("));
      Serial.print(mqtt.state());
      Serial.println(F(")!"));
      return false;
    }
    const String commande(F("mason-jar/command/#"));
    mqtt.subscribe(commande.c_str(), 1);  // Qos = 1
    
    const String connected( nom + F(" connected.") );
    mqtt.publish(hello.c_str(), connected.c_str());
    return true;
  }

private:
  const String adresse;
  const unsigned port;
  const String nom;
  WiFiClient wifi;
  PubSubClient mqtt;

  std::list< std::pair<String, String> > commands;

};
