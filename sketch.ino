#include "WiFi.h"
#include <PubSubClient.h>
#include "DHT.h"
#include <ArduinoJson.h>
#include "secrets.h"
#include <WiFiClientSecure.h>
#define MY_SUB "esp32/sub"
#define MY_PUB "esp32/pub"
#define SENSOR_PIN 15
#define SENSOR_TYPE DHT22
float humidity_Value;
float temperature_Value;

DHT sensor(SENSOR_PIN, SENSOR_TYPE);

WiFiClientSecure secureNet = WiFiClientSecure();
PubSubClient mqttClient(secureNet);

void setupWiFiAndAWS() {
  WiFi.mode(WIFI_STA);
  Serial.print("Setup initiated !!!");
  WiFi.begin(NETWORK_USER, NETWORK_SECRET);
  Serial.print("#");
  Serial.println("Attempting to establish an internet connectivity !!!");
  
  while (WiFi.status() != WL_CONNECTED) {
     Serial.print("#");
     delay(600);

    
   
  }

  secureNet.setPrivateKey(AWS_SECRET_KEY);
  secureNet.setCertificate(AWS_THING_CERTIFICATE);
  secureNet.setCACert(AWS_CA);  
  mqttClient.setServer(AWS_CORE_THING, 8883);
  mqttClient.setCallback(awsMessageReceived);
   Serial.print("#");
  Serial.println("Attempting to initiate a connection with the IoT Core device !!!");

  while (!mqttClient.connect(My_THING_NAME)) {
      Serial.print("#");
     delay(100);
     
   
   
  }

  if (!mqttClient.connected()) {
     Serial.print("#");
    Serial.println("Unable to handle IoT Core request !!! ");
    return;
  }

  mqttClient.subscribe(MY_SUB);
     Serial.print("#");
  Serial.println("Successfully Connected to IOT_CORE THING !!!");
}

void sendSensorData() {
  StaticJsonDocument<200> dataDoc;
  dataDoc["humidity"] = humidity_Value;
  dataDoc["temperature"] = temperature_Value;
  char dataBuffer[512];
  serializeJson(dataDoc, dataBuffer); 

  mqttClient.publish(MY_PUB, dataBuffer);
}

void awsMessageReceived(char* rec, byte* msg, unsigned int len) {
  Serial.print("Receiving messages on ");
  Serial.println(rec);
  StaticJsonDocument<200> recDoc;
  deserializeJson(recDoc, msg);
  const char* receivedMessage = recDoc["msg"]; 
}

void displaySensorReadings() {
  Serial.print(F(" Temp - "));

  Serial.print(temperature_Value);

  Serial.print(F(" Celsius  Humid- "));
  
  Serial.print(humidity_Value);
  
  Serial.println(F(" Percent "));
}

void setup() {
  Serial.begin(74880);

  setupWiFiAndAWS();
  sensor.begin();
}

void loop() {
  humidity_Value = sensor.readHumidity();
  temperature_Value = sensor.readTemperature();

  if (isnan(humidity_Value) || isnan(temperature_Value)) {
    Serial.println(F("Error receiving data"));
    return;
  }

  displaySensorReadings();
  sendSensorData();
  mqttClient.loop();
  delay(1000);
}

