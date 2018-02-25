
const String HUB_IP = "192.168.64.1"; //raspberry pi hub ip
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#define SERVER_PORT 4132 //Receive port

const char* ssid = "BioBloom";
const char* password = "teamholly";
String mac_address_string;
const String HUB_PORT = "80"; //transmit port
IPAddress ip; 
//local mac and ip addresses
ESP8266WebServer server(SERVER_PORT);


void setup() {
  //START WIFI, CONNECT TO HUB
  WiFi.hostname(mac_address_string);
  WiFi.begin(ssid, password);
  WiFi.macAddress(mac);
  mac_address_string = String(mac);
  
  
 //REQUESTS ARE RECEIVED ON HTTP://THIS_IP:THIS_PORT/______
 // e.g. htttp://192.168.64.2:4132/data_request


 
 //WHEN DATA REQUEST SIGNAL IS RECEIVED 
  server.on("/data_request",[]()
  {
  Serial.println("DATA REQUEST RECIEVED");
  sensor_info_request(); 
  });


 //WHEN ACTION REQUEST SIGNAL IS RECEIVED
  server.on("/action_request",[]()
  {
  Serial.println("ACTION REQUEST RECIEVED");
  String received_id = server.arg("id");
  perform_action_request(received_id);
  });
  
  server.begin(); //START SERVER
}



void loop() {
  server.handleClient(); //CHECKS FOR THE ABOVE REQUESTS



 //CHECK SPI FOR INCOMING SENSOR DATA
transmit_sensor_data(int light_level, int air_humidity, int soil_humidity, int temperature, int water_level);
}




void perform_action_request(String action_id){

  if(action_id=="water"){ //i.e water the plant
  //SEND OVER SPI TO WATER THE PLANT
  }

  if(action_id=="leds"){ //i.e turn on leds
  //SEND OVER SPI TO TURN ON LEDS
  }
}

void sensor_info_request(){
  //SEND OVER SPI TO SEND ALL SENSOR INFO.
  //DONT WAIT FOR RESPONSE, RESPONSE HANLED IN LOOP WHERE SPI CHECKS FOR INCOMING DATA
}


void transmit_sensor_data(int light_level, int air_humidity, int soil_humidity, int temperature, int water_level){
  if(WiFi.status() == WL_CONNECTED){ //if wifi connected
 
  HTTPClient http; //START NEW HTTP CLIENT CALLED "http"
  ip = WiFi.localIP(); //used with ip.toString
  
  http.begin("http://" + HUB_IP + ":" + HUB_PORT + "/sensor_data.php");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.POST("id=" + String(mac_address_string) + "&local_ip=" + ip.toString() + "&light_level=" + String(light_level) + "&air_humidity=" + String(air_humidity)+ "&soil_humidity=" + String(soil_humidity)+ "&temperature=" + String(temperature)+ "&water_level=" + String(water_level));
  String payload = http.getString();
  Serial.println(payload);
  Serial.println(httpCode);
  http.end();
  }
}

