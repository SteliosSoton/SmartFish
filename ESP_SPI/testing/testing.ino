#include <SPI.h>         // https://www.arduino.cc/en/Reference/SPI
#include <Arduino.h>
uint8_t ss_pin;

void setDataBits(uint16_t bits) {
    const uint32_t mask = ~((SPIMMOSI << SPILMOSI) | (SPIMMISO << SPILMISO));
    bits--;
    SPI1U1 = ((SPI1U1 & mask) | ((bits << SPILMOSI) | (bits << SPILMISO)));
}

void write(char data) {
    //while(SPI1CMD & SPIBUSY) {}
    SPI1W0 = data;
    SPI1CMD |= SPIBUSY;
    while(SPI1CMD & SPIBUSY);
}
void writeData(char data)     // convert char data into format SPI.transfer likes
{
  
    digitalWrite(ss_pin, LOW);
    //uint8_t sent = SPI.transfer(data);   // send data byte
    write(data);
    //Serial.println(sent);
    digitalWrite(ss_pin, HIGH);    
    //delay(10);
}

void setup() {
   /*  MATT SPI stuffs  */
  Serial.begin(115200);
  SPI.begin();                  // initialises the SPI bus by setting SCK, MOSI & SS as outputs, pulling SCK & MOSI low, and SS high
  ss_pin = SS;                  // set SS pin
  //SPI.setFrequency(0x187500);
  SPI.beginTransaction(SPISettings(187500, MSBFIRST, SPI_MODE0));
  pinMode(ss_pin, OUTPUT);      // set SS as output
  digitalWrite(ss_pin, HIGH);   // set SS high to start (no data transfer to begin)
  setDataBits(8);
  /* ----------------- */
  
}

void loop() {
  for (char i = 0; i < 255; i++) {
    writeData(i);
    delay(5);
  }

}
