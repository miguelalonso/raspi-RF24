/*
http://blog.riyas.org/search/label/radio

*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
// For using the temperature sensor DS18S20
#include <OneWire.h> 
//int DS18S20_Pin = 8; //DS18S20 Signal pin on digital 2
//OneWire ds(DS18S20_Pin);  // on digital pin 2

float datos[5];  // 2 element array holding Joystick readings

//for nrf24 debug
int serial_putc( char c, FILE * ) 
{
  Serial.write( c );
  return c;
} 

//for nrf24 debug
void printf_begin(void)
{
  fdevopen( &serial_putc, 0 );
}


//nRF24 set the pin 9 to CE and 10 to CSN/SS
// Cables are:
//     SS       -> 10
//     MOSI     -> 11
//     MISO     -> 12
//     SCK      -> 13

RF24 radio(6,7);

//we only need a write pipe, but am planning to use it later
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL,0xF0F0F0F0D2LL };

// here we can send up to 30 chars
char SendPayload[31] = "blog.riyas.org";
long randNumber;

void setup(void) {
  Serial.begin(9600); //Debug 
  printf_begin();
  //nRF24 configurations
  radio.begin();
  //radio.setChannel(0x4c);
  //radio.setAutoAck(1);
  //radio.setRetries(15,15);
  //radio.setDataRate(RF24_250KBPS);
  //radio.setPayloadSize(32);
  
  //radio.openReadingPipe(1,pipes[0]);
  radio.openWritingPipe(pipes[1]);
  radio.startListening();
  radio.printDetails(); //for Debugging
}

void loop() {
  
  datos[0] =  random(3000);;
  datos[1] =  -random(3000);;
  datos[2] = 129.25;
  datos[3] = -analogRead(1);
  datos[4] = analogRead(2);
   Serial.println (datos[0]);
  //Get temperature from sensor
  //  float temperature = getTemp();
    float temperature = 25.25;
  // Assign temperature to payload, here am sending it as string
  //dtostrf(temperature,2,2,SendPayload);
  
  //add a tag
 // strcat(SendPayload, "X");   // add first string

  //send a heartbeat
  radio.stopListening();
  //bool ok = radio.write(&SendPayload,strlen(SendPayload));
  bool ok = radio.write( datos, sizeof(datos) );
 // Serial.println (sizeof(datos));
  radio.startListening(); 
  //Serial.println(SendPayload);  

  // slow down a bit
  delay(1000);  
}


// Getting temperature from DS18S20

/*
float getTemp(){
  //returns the temperature from one DS18S20 in DEG Celsius

  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      ds.reset_search();
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end

  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); // Read Scratchpad

  
  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }
  
  ds.reset_search();
  
  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;
  
  return TemperatureSum;
  
}
*/
