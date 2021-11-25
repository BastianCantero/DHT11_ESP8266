
//Importamos las librerias necesarias, para trabajr con el modulo ESP8266 y Firebase
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

//Declaramos variable de acceso al proyecto en Firebase
#define FIREBASE_HOST "** FIREBASE_HOST HERE **"
#define FIREBASE_AUTH "** FIREBASE_AUTH HERE **"

//Declaramos variable de acceso a la red WIFI
#define WIFI_SSID "** WIFI_SSID HERE **"
#define WIFI_PASSWORD "** WIFI_PASSWORD HERE **"

FirebaseData firebaseData;

//Incluimos la libreria del modulo DHT11 y el pin al que estara conectado
#include "DHTesp.h"
#define DHTpin 5 //Pin D1 en modulo ESP8266
DHTesp dht;

void setup() {

  Serial.begin(9600);

  Serial.println("Serial communication started\n\n");  
           
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);


  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  Firebase.reconnectWiFi(true);
  delay(1000);


 dht.setup(DHTpin, DHTesp::DHT11);
  
}

void loop() { 


  dht11Firebase();
  
}

void dht11Firebase(){

  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  Firebase.setInt(firebaseData, "/temperatura", temperature);
  Firebase.setInt(firebaseData, "/humedad", humidity);
  
}
