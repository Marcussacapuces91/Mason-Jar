#!/usr/bin/env python
# -*- coding: utf-8 -*-

##
# Copyright 2020 Marc SIBERT
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
##

"""Module documentation goes here
   and here
   and ...
"""

import logging
import paho.mqtt.client as mqtt
import re
import json

logging.basicConfig(level=logging.DEBUG)

class App:
    def __init__(self, host="localhost", port=1883):
        self._host = host
        self._port = port
        self._nom = "control"
        
        self._client = mqtt.Client(self._nom)
        self._client.will_set("mason-jar/hello/{}".format(self._nom), '{"verb":"disconnect"}', qos=0, retain=False)
        try:
            self._client.connect(self._host, self._port)
        except Exception as e :
            logging.critical(e)
            exit(1)
            
        self._client.loop_start()

        err = self._client.publish("mason-jar/hello/{}".format(self._nom), '{"verb":"connect"}')
        if err.rc != 0:
            logging.critical( "Erreur de publication ({})!".format(err.rc) )
            exit(err.rc)

        self._client.message_callback_add("mason-jar/hello/#", self.on_message_hello)
        self._client.subscribe("mason-jar/#")
        
    def on_message_hello(self, client, userdata, message):
        print(message.topic+" "+str(message.payload))
        sp = re.split(r'/', message.topic, 3)
        try:
            msg = json.loads( message.payload.decode('utf-8') )
            if msg['verb'] == 'connect' :
                print("{} as connected.".format(sp[2]))
                self._client.publish("mason-jar/command/{}".format(sp[2]), '{"verb":"init"}')
            else:
                logging.warning("Verbe non reconnu ({})!".format(msg['verb']))

        except JSONDecodeError:
            logging.warning("Message non décodé ({})!".format(message.payload.decode('utf-8')))
            
        
        

if __name__ == '__main__':
    app = App()
    while True:
        pass
    
