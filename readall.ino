#include <SPI.h>
 
//SRAM opcodes
#define RDSR        5
#define WRSR        1
#define READ        3
#define WRITE       2
 
byte cs_pin[1] = {10}; //cs_pin location of the two SRAMS

uint32_t maxram = 131072; //number of bytes in 23LC1024 SRAM
uint32_t maxpage = 4096;  //number of pages in 23LC1024 SRAM

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-*/
//Byte transfer functions
//here we read and write one byte at a time at each address

uint8_t Spi23LC1024Read8(uint32_t address, uint8_t cs_pin)
{
  uint8_t read_byte;
  
  digitalWrite(cs_pin, LOW);   
  SPI.transfer(READ);
  SPI.transfer((uint8_t)(address >> 16));
  SPI.transfer((uint8_t)(address >> 8) & 0xFF);
  SPI.transfer((uint8_t)address);
  read_byte = SPI.transfer(0x00);
  digitalWrite(cs_pin, HIGH); 

  Serial.print("READ : ");
  Serial.println(read_byte);
  
  return read_byte;
}

void Spi23LC1024Write8(uint32_t address, uint8_t data_byte, uint8_t cs_pin) 
{
  digitalWrite(cs_pin, LOW); 
  SPI.transfer(WRITE);
  SPI.transfer((uint8_t)(address >> 16) & 0xff);
  SPI.transfer((uint8_t)(address >> 8) & 0xff);
  SPI.transfer((uint8_t)address);
  SPI.transfer(data_byte);
  digitalWrite(cs_pin, HIGH); 

  Serial.print("WRITE : ");
  Serial.println(data_byte);
 }
 
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-*/
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
//      Serial.println(read_page);
  }
  digitalWrite(cs_pin, HIGH);   
}

void Spi23LC1024Write32(uint32_t address, uint8_t* buffer170, uint8_t cs_pin)
{
    uint32_t i;
    
    digitalWrite(cs_pin, LOW); 
    SPI.transfer(WRITE);
    SPI.transfer((uint8_t)(address >> 16));
    SPI.transfer((uint8_t)(address >> 8));
    SPI.transfer((uint8_t)address);
    
    for (i = 0; i < 32; i++)
    {
        SPI.transfer(buffer170[i]);
    }
    digitalWrite(cs_pin, HIGH); 
}
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-*/

uint32_t i, j, n; 
uint32_t value; 
uint8_t set_value = 170; 
uint32_t num = 0; 
uint32_t total_send = 10; 
//uint8_t buffer170[1] = {170}; 
uint8_t buffer170[32] = {170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170}; 
uint8_t buff[32];

void setup(void) 
{
  Serial.begin(9600);
  SPI.begin();

  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  
//  pinMode(9, OUTPUT);
//  digitalWrite(9, HIGH); 

  /*----THIS IS TO READ ALL BYTES IN THE TWO SRAMS ONE AT A TIME----*/
//  Serial.println("BYTE MODE");
//  digitalWrite(10, LOW);
////  for (j = 0; j < 2; j++) 
////  {
//    num = 0;  
////    for (i = 0; i < maxram; i++)
//    for (i = 0; i < total_send; i++)
//    {
//      Spi23LC1024Write8(i, (uint8_t)set_value++, cs_pin[j]);
//    }
////    for (i = 0; i < maxram; i++)
//    for (i = 0; i < total_send; i++)
//    {
//      value = Spi23LC1024Read8(i, cs_pin[j]);
//        Serial.print(value, HEX); //returns the value it holds in HEX format
//        Serial.print(" at: ");
//        Serial.println(i, HEX);  //returns the address at which this occurs in HEX format
//        Serial.print("\n");
//      if (value != set_value)  //will check if any of the 131,072 bytes is not equal to the value we set it: 170
//      {
//        num++;
//       }
//     }
//
//     digitalWrite(10, HIGH);
//     
//     Serial.print("Summary read from ");
//     Serial.print(cs_pin[j]);  //returns the cs line/SRAM it was reading from
//     Serial.print(". Error : ");
//     Serial.print(num); //returns no. of errors occured in this cs_line/SRAM
//     Serial.print(". Correct : ");
//     Serial.println(total_send - num); //returns no. of errors occured in this cs_line/SRAM
//     Serial.print("------------------------------------------\n");
//     delay(1000); //To give the cs_line time to die down
////  }

  /*----THIS IS TO READ ALL PAGES IN THE TWO SRAMS ONE AT A TIME----*/
  Serial.println("PAGE MODE");
  
  num = 0;
//  for (i = 0; i < maxpage; i++)
//  { 
//    Spi23LC1024Write32(i, buffer170, 10);
//  }
  for (i = 0; i < 10; i++) 
  {
    Spi23LC1024Read32(i, cs_pin[j],buff);
    for (n = 0; n < 32; n++)  //because each page consists of a further 32 bytes we need to check
    {
//      if (buff[n] != set_value)
//      {
//        Serial.print(value, HEX);
//        Serial.print(" at: ");
//        Serial.println(n, HEX); 
//        num++;
//      }
      Serial.println(buff[n]); 
    }
  }
//  Serial.print(10);  //returns the cs line/SRAM it was reading from
//  Serial.print(":");
//  Serial.println(num);  //How many errors occured in this cs_line/SRAM
  delay(1000); //To give the cs_line time to die down

}
 
void loop() 
{

}

