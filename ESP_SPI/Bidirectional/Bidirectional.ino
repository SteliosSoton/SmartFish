#include <SPI.h>

void setup() {
  Serial.begin(115200);
  digitalWrite(SS, HIGH);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
}

void loop() {
  byte Mvalsent, Mvalreceived;


  for(int i=0; i<255; i++)
  {
    digitalWrite(SS, LOW);
    delay(10);
    
    Mvalsent = i;
    Mvalreceived = SPI.transfer(Mvalsent);    // Mvalsent -> transmit buffer | recieve buffer -> Mvalreceived

    Serial.print("sent: ");
    Serial.print(Mvalsent);
    Serial.print("\t\t received: ");
    Serial.println(Mvalreceived);
    
    delay(10);
    digitalWrite(SS, HIGH);
    
    delay(1000);
  }

  delay(1000);
}
