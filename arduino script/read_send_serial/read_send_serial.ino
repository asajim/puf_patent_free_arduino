#include <SPI.h>
 
//SRAM opcodes
#define RDSR        5
#define WRSR        1
#define READ        3
#define WRITE       2
 
byte cs_pin = 10; //cs_pin location of the two SRAMS

//uint32_t maxram = 131072; //number of bytes in 23LC1024 SRAM
uint32_t maxpage = 4096;  //number of pages in 23LC1024 SRAM
//uint32_t maxpage = 1024;  //number of pages in 23K256 SRAM

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-*/
//Page transfer Functions
//here we can read and write 32 bytes at each address

void Spi23LC1024Read32(uint32_t address, uint8_t cs_pin, uint8_t* buff)
{
  uint32_t i; 
  uint8_t read_page; 

  digitalWrite(cs_pin, LOW);  
  SPI.transfer(READ);
  SPI.transfer((uint8_t)(address >> 16));
  SPI.transfer((uint8_t)(address >> 8)); 
  SPI.transfer((uint8_t)address);
  
  for (i = 0; i < 32; i++)
  {
      read_page = SPI.transfer(0x00);
      buff[i] = read_page;
  }
  digitalWrite(cs_pin, HIGH);   
}

void Spi23LC1024Write32(uint32_t address, uint8_t buffer170, uint8_t cs_pin)
{
    uint32_t i;
    
    digitalWrite(cs_pin, LOW); 
    SPI.transfer(WRITE);
    SPI.transfer((uint8_t)(address >> 16));
    SPI.transfer((uint8_t)(address >> 8));
    SPI.transfer((uint8_t)address);
    
    for (i = 0; i < 32; i++)
    {
        SPI.transfer(buffer170);
    }
    digitalWrite(cs_pin, HIGH); 
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-*/

uint32_t i, j, n; 
uint32_t value; 
uint32_t num = 0; 
uint32_t total_send = 10; 
uint8_t buff[32];
uint32_t index = 0;
uint8_t total_buff[32*128];
int inByte;

int pin_hold = 11;
int pin_select = 10;
int pin_mosfet = 12;

//int power = 2;
//int transistor = 12;

void setup(void) 
{
  Serial.begin(9600);
//  SPI.begin();

  delay(500);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pin_select, OUTPUT);
  pinMode(pin_hold, OUTPUT);
  pinMode(pin_mosfet, OUTPUT);

//  pinMode(power, OUTPUT);    
//  pinMode(transistor, OUTPUT);     
//  digitalWrite(power, HIGH);

//  digitalWrite(pin_mosfet, LOW);
//  readSRAM();
//  SPI.end();  

//  digitalWrite(pin_select, HIGH);
//  digitalWrite(pin_hold, HIGH);

//  delay(500);

//  pinMode(52, OUTPUT);
//  digitalWrite(52, HIGH);
//
//  pinMode(51, OUTPUT);
//  digitalWrite(51, HIGH);
}

void readSRAM(){
  SPI.begin();
  digitalWrite(pin_select, LOW);
  digitalWrite(pin_hold, HIGH);
  digitalWrite(pin_mosfet, HIGH);
  delay(100);

// write
//  for (j = 0; j < 1; j++){
//    index = 0;
//    for (i = 0; i < 128; i++) 
//    {
//      Spi23LC1024Write32(j*128+i, (uint8_t) 6, cs_pin);
//    }
//  }
   
// read
// all memory
//  for (j = 0; j < maxpage/128; j++){
// partial
  for (j = 0; j < 2; j++){
    index = 0;
    for (i = 0; i < 128; i++) 
    {
      Spi23LC1024Read32(j*128+i, cs_pin,buff);
      memcpy(&total_buff[index], buff, sizeof(buff));
      index += 32;
    }

    i = 0;
//    for (i = 0; i< index; i++){
//      Serial.println(total_buff[i], HEX);
//    }
    for (i = 0; i< index; i=i+4){
      Serial.println((uint32_t) total_buff[i] << 24 | (uint32_t) total_buff[i+1] << 16 | (uint32_t) total_buff[i+2] << 8 | total_buff[i+3], HEX);
    }

//    for (i = 0; i< index; i=i+8){
//      Serial.println((uint64_t) total_buff[i] << 54 | (uint64_t) total_buff[i+1] << 48 | (uint64_t) total_buff[i+2] << 40 | (uint64_t) total_buff[i+3] << 32 | (uint64_t) total_buff[i+4] << 24 | (uint64_t) total_buff[i+5] << 16 | (uint64_t) total_buff[i+6] << 8 | total_buff[i+7], HEX);
//    }
     
  }

  digitalWrite(pin_select, HIGH);
//  digitalWrite(pin_hold, LOW);
  digitalWrite(pin_hold, HIGH);
  digitalWrite(pin_mosfet, LOW);

  SPI.end();

  pinMode(52, OUTPUT);
  digitalWrite(52, HIGH);

  pinMode(51, OUTPUT);
  digitalWrite(51, HIGH);

}
 
void loop() 
{
//    digitalWrite(pin_mosfet, HIGH);   // turn the LED on (HIGH is the voltage level)
    readSRAM();
    delay(30000);               // wait for a second
//    digitalWrite(pin_mosfet, LOW);    // turn the LED off by making the voltage LOW
//    delay(3000);               // wait for a second
//  readSRAM();
//  delay(10000);
//  if (Serial.available() > 0){
//    inByte = Serial.read();
//    if (inByte == 'a'){
//      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
////      readSRAM();
//      Serial.println("ON");
//      inByte = 'q';
//    }else if(inByte == 's'){
//      digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
//      Serial.println("OFF");
//      inByte = 'q';
//    }
//  }
}
