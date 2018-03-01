int version_number = 1;
const String HUB_IP = "192.168.5.1"; //raspberry pi hub ip
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#define SERVER_PORT 4132 //Receive port

/* MATT SPI Stuff */
#include <SPI.h>         // https://www.arduino.cc/en/Reference/SPI

typedef struct data {         //Create new type for holding transmission data
  char versionNum;            //Version of device sending the data
  char command;               //Command hex code
  char commandInfoLength;     //Length of data sent over command and before end
  char commandInfo[50];       //Buffer for command info
  char feedback;              //If sender wants data in return
}data;                        //Call this new type of variable 'data'

data tx;
int ADCdata[4];

uint8_t ss_pin;
const char startByte = 0x7E;  // constant start byte value
const char endByte = 0x7F;    // constant end byte value



const char* ssid = "BioBloom";
const char* password = "teamholly";
const String HUB_PORT = "80"; //transmit port
String mac_address_string;
int run_time;
IPAddress ip; 
//local mac and ip addresses
ESP8266WebServer server(SERVER_PORT);


String mac2String(byte mac[])
{
  String s;
  for (byte i = 0; i < 6; ++i)
  {
    char buf[3];
    if (mac[i]<16){
    sprintf(buf, "%1X", mac[i]);
    s+= 0;
    s += buf;
    }
    else{
      sprintf(buf, "%2X", mac[i]);
    s += buf;
    }
    if (i < 5) s += ':';
  }
  return s;
}

void refresh(){
  if(WiFi.status() != WL_CONNECTED){ //if wifi is disconnected set run_time low so the else if below will run once reconnected
    run_time = 0;
  }
  else if((WiFi.status() == WL_CONNECTED)&&(run_time ==0)){ //if wifi is now connected and has been disconnected before/the just been turned on
    run_time = 1;
    Serial.println("attempting update");
    update_ip();
  }
}

void update_ip(){
  if(WiFi.status() == WL_CONNECTED){
  HTTPClient http;
  ip = WiFi.localIP();
  http.begin("http://" + HUB_IP + ":" + HUB_PORT + "/update_ip.php");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.POST("&mac=" + String(mac_address_string) + "&local=" + ip.toString() + "&vers=" + String(version_number));
  String payload = http.getString();
  Serial.println(payload);
  Serial.println(httpCode);
  http.end();
  }
}

/*  ----------------------------  MATT SPI FUNCTIONS  ----------------------------  */
void writeData(uint8_t data)
{
    digitalWrite(ss_pin, LOW);        // ss must be low during transmisison
    delay(10);
    char test = SPI.transfer(data);   // send data byte
    Serial.println(test);
    delay(10);
    digitalWrite(ss_pin, HIGH);       // ss must be high between transmissions
    delay(100);
}
    
void writeData(char data)     // convert char data into format SPI.transfer likes
{
  //Serial.print("writeData char: ");
  //Serial.println(data);
  writeData((uint8_t)data);
}

void sendTx(data txSend, int feedback){               // move through data to send, sending each hex byte over SPI individually
  writeData(startByte);                               // send start byte marker
  writeData(txSend.versionNum);                       // send version
  writeData(txSend.command);                          // send command marker (hex code)
  writeData(txSend.commandInfoLength);                // send the number of following data bytes
  for(uint8_t i=0; i<txSend.commandInfoLength; i++){  // loop through data bytes
    writeData(txSend.commandInfo[i]);                 // send each hex data byte individually
  }
  writeData(txSend.feedback);                         // send feedback byte
  writeData(endByte);                                 // send end byte marker

  if(feedback == 1){  // if feedback is wanted
    delay(100);
    readADCData();    // pulse slave to empty its transmit register into master
  }
}

//uint8_t * data
void readADCData()
{
  //Serial.println("readData()");

  digitalWrite(ss_pin, LOW);    
  SPI.transfer(0x07d);            // send marker for start of 2-way transmission
  digitalWrite(ss_pin, HIGH);
  
  for(uint8_t i=0; i<5; i++) {
    digitalWrite(ss_pin, LOW);
    delay(10);
    ADCdata[i] = SPI.transfer(i); // send increment values to get the 3 data bytes
    //Serial.println(ADCdata[i]); // and store what the slave send back in ADCdata array
    delay(10);
    digitalWrite(ss_pin, HIGH);
    delay(10);
  }

  digitalWrite(ss_pin, LOW);
  SPI.transfer(0x07f);            // send marker for end of transmission 
  digitalWrite(ss_pin, HIGH);

  doSomethingWithADCData();       // use the recieved data to do something... (database tings?)
}

void doSomethingWithADCData(){
  int batteryData = ADCdata[1];   // convert back to correct format
  int lightData = ADCdata[2];                 // convert light format
  int humidityData = ADCdata[3];              // convert humidity format
  int data1 = ADCdata[4];                     // 50 = ok, 100 = error
  int failed = 0;                             // variable to track failure on recieved data (needs to be reset each time to 0)

  // did the slave send any data? Or did it just echo back what it was sent?
  if(batteryData == 0 && lightData == 1 && humidityData == 2){  // if slave doesn't send any data 0, 1, 2 will be echoed back
    Serial.println("[Transmit Mode - FAILED]");                 // if this happens we need to send getData command over SPI again
  }
  else{
    Serial.println("[Transmit Mode - SUCCESSFUL]");
  }

  // did the slave pass all it's internal tests? did it send the data it wanted to?
  if(data1 == 100){   
    Serial.println("[Slave Data Send - FAILED]");
    failed = 1;     // resend command to get ADC data
  }
  else if(data1 == 50){
    Serial.println("[Slave Data Send - SUCCESSFUL]");
    failed = 0;
  }
  else{
    Serial.println("[Slave Data Send - REALLY FAILED!?]");
    failed = 1;     // resend command to get ADC data
  }
  
  Serial.print("Battery: ");
  Serial.println(batteryData);
  Serial.print("Temp: ");
  Serial.println(lightData);
  Serial.print("Light: ");
  Serial.println(humidityData);
  Serial.print("Data: ");
  Serial.println(data1);

  if(failed == 1){
    Serial.println("[resending ADC data request...]");
    sensor_info_request(); // call the functions to get the data again
  }
  else if(failed == 0){
    Serial.println("[SUCCESS!]");
  }
}

/*  ----------------------------  End SPI functions  ----------------------------  */

void perform_action_request(String action_id){

  if(action_id=="water"){ //i.e water the plant
  //SEND OVER SPI TO WATER THE PLANT
  }

  if(action_id=="leds"){ //i.e turn on leds
  //SEND OVER SPI TO TURN ON LEDS
  }
}

void perform_audio_request(String track_id, String volume_id){
  //SEND OVER SPI TRACK NO AND VOLUME LEVEL
  int track = atoi(track_id.c_str());   // convert track to int
  char trackC[2];                       // char aray to hold track char
  int trackHex;                         // int to hold track hex
  sprintf(trackC, "0x%d", track);       // int to char
  sscanf(trackC, "%x", &trackHex);      // char to hex
  
  int vol = atoi(volume_id.c_str());    // convert vol to int
  char volC[2];                         // char aray to hold track char
  int volHex;                           // int to hold track hex
  sprintf(volC, "0x%d", vol);           // int to char
  sscanf(volC, "%x", &volHex);          // char to hex
  
  Serial.print("atoi: ");               // display "track num : volume num"
  Serial.print(trackHex);
  Serial.print(" : ");
  Serial.println(volHex);
  
  tx.versionNum = 0x01;           // version 1.0
  tx.command = 0x03;              // audio command
  tx.commandInfoLength = 0x03;    // 3 data codes to follow
  tx.commandInfo[0] = 0x22;       // Command - Play with volume
  tx.commandInfo[1] = volHex;     // Volume - 30 (0x1E)
  tx.commandInfo[2] = trackHex;   // Track - 3 (0x03)
  tx.feedback = 0x00;             // no feedback needed
  sendTx(tx, 0);                  // send this command over SPI (no feedback)
}

void sensor_info_request(){
  //SEND OVER SPI TO SEND ALL SENSOR INFO.
  //DONT WAIT FOR RESPONSE, RESPONSE HANLED IN LOOP WHERE SPI CHECKS FOR INCOMING DATA
  tx.versionNum = 0x01;           // version 1.0
  tx.command = 0x02;              // sensor data request
  tx.commandInfoLength = 0x03;    // 3 data codes to follow
  tx.commandInfo[0] = 0x02;       // Command - request sensor data (0x02)
  tx.commandInfo[1] = 0x01;       // dummy data
  tx.commandInfo[2] = 0x00;       // dummy data
  tx.feedback = 0x01;             // feedback needed
  Serial.println("sensor_info_request sendTx");
  sendTx(tx, 1);                  // send this command over SPI (request feedback)
}


void transmit_sensor_data(int light_level, int air_humidity, int soil_moisture, int temperature, int water_level, int battery_level){
  if(WiFi.status() == WL_CONNECTED){ //if wifi connected
 
  HTTPClient http; //START NEW HTTP CLIENT CALLED "http"
  ip = WiFi.localIP(); //used with ip.toString
  
  http.begin("http://" + HUB_IP + ":" + HUB_PORT + "/sensor_data.php");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.POST("&mac=" + mac_address_string + "&light_level=" + String(light_level) + "&air_humidity=" + String(air_humidity)+ "&soil_mositure=" + String(soil_moisture)+ "&temperature=" + String(temperature)+ "&water_level=" + String(water_level) +"&battery_level=" + String(battery_level));
  String payload = http.getString();
  Serial.println(payload);
  Serial.println(httpCode);
  http.end();
  }
}

/* ------------------------------------------------------------------- */

void setup() {
  pinMode(5, OUTPUT); // D1 output LED
  digitalWrite(5, LOW); //WRITE LED LOW
  Serial.begin(115200);
  byte mac[6];
  WiFi.macAddress(mac);
  mac_address_string = mac2String(mac);
  Serial.println(" ");
  Serial.println(mac_address_string);
  run_time = 0;

  //START WIFI, CONNECT TO HUB
  WiFi.hostname(mac_address_string);
  WiFi.begin(ssid, password);
  //while(WiFi.status()!= WL_CONNECTED){
  //  delay(500);
  //  Serial.print(".");
  //}
   ip = WiFi.localIP();
  Serial.println(ip);
  
 //REQUESTS ARE RECEIVED ON HTTP://THIS_IP:THIS_PORT/______
 // e.g. htttp://192.168.5.2:4132/data_request


 
 //WHEN DATA REQUEST SIGNAL IS RECEIVED 
  server.on("/data_request",[]()
  {
  Serial.println("DATA REQUEST RECIEVED");
  digitalWrite(5, HIGH);
  delay(50);
  digitalWrite(5, LOW);
  sensor_info_request(); 
  });


 //WHEN ACTION REQUEST SIGNAL IS RECEIVED
  server.on("/action_request",[]()
  {
  Serial.println("ACTION REQUEST RECIEVED");
  digitalWrite(5, HIGH);
  delay(50);
  digitalWrite(5, LOW);
  String received_id = server.arg("id");
  perform_action_request(received_id);
  });

  //WHEN AUDIO REQUEST SIGNAL IS RECEIVED
  server.on("/audio_request",[]()
  {
  Serial.println("AUDIO REQUEST RECIEVED");
  digitalWrite(5, HIGH);
  delay(50);
  digitalWrite(5, LOW);
  String track_id = server.arg("track");
  String volume_id = server.arg("volume");
  Serial.println(track_id);
  Serial.println(volume_id);
  
  perform_audio_request(track_id, volume_id);
  });


  /*  MATT SPI stuffs  */
  SPI.begin();                  // initialises the SPI bus by setting SCK, MOSI & SS as outputs, pulling SCK & MOSI low, and SS high
  ss_pin = SS;                  // set SS pin
  pinMode(ss_pin, OUTPUT);      // set SS as output
  digitalWrite(ss_pin, HIGH);   // set SS high to start (no data transfer to begin)
  /* ----------------- */

  
  server.begin(); //START SERVER
}

int x = 1;

void loop() {
  server.handleClient(); //CHECKS FOR THE ABOVE REQUESTS
  refresh();  //will check if ip needs updated

  /* MATT SPI STUFFS */
  delay(1000);

  if(x==1) sensor_info_request(); // manually call the getADCdata function

  delay(1000);

  x++;
  /* --------------- */
  
 //CHECK SPI FOR INCOMING SENSOR DATA
 
//transmit_sensor_data(int light_level, int air_humidity, int soil_moisture, int temperature, int water_level, int battery_level);
}

