#include <SPI.h>
 
//SRAM opcodes
#define RDSR        5
#define WRSR        1
#define READ        3
#define WRITE       2
 
byte cs_pin = 10; //cs_pin location of the two SRAMS

//uint32_t maxram = 131072; //number of bytes in 23LC1024 SRAM
//uint32_t maxpage = 4096;  //number of pages in 23LC1024 SRAM
uint32_t maxpage = 1024;  //number of pages in 23K256 SRAM

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

void setup(void) 
{
  Serial.begin(9600);
  SPI.begin();

  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  delay(1000);

  // timer start
//  uint32_t ts1 = millis();
//  Serial.println("start");
//  
//  for (j = 0; j < 16; j++){
//    index = 0;
//    for (i = 0; i < 128; i++) 
//    {
//      Spi23LC1024Read32(j*128+i, cs_pin,buff);
////      memcpy(&total_buff[index], buff, sizeof(buff));
//      index += 32;
//    }
//  
////    for (i = 0; i< index; i++){
////      Serial.println(total_buff[i], HEX);
////    }
//  }

  // read
  for (j = 0; j < 8; j++){
    index = 0;
    for (i = 0; i < 128; i++) 
    {
      Spi23LC1024Read32(j*128+i, cs_pin,buff);
      memcpy(&total_buff[index], buff, sizeof(buff));
      index += 32;
    }
  
    for (i = 0; i< index; i++){
      Serial.println(total_buff[i], HEX);
    }
  }

  // write
//  for (i = 0; i < maxpage; i++) {
//    Spi23LC1024Write32(i, (uint8_t) 255, cs_pin);
//  }

  // timer finish
//  uint32_t ts2 = millis();
//  Serial.println("finish");
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
}
 
void loop() 
{

}

void print_binary(int v, int num_places)
{
    int mask=0, n;

    for (n=1; n<=num_places; n++)
    {
        mask = (mask << 1) | 0x0001;
    }
    v = v & mask;  // truncate v to specified number of places

    while(num_places)
    {

        if (v & (0x0001 << num_places-1))
        {
             Serial.print("1 ");
        }
        else
        {
             Serial.print("0 ");
        }

        --num_places;
//        if(((num_places%4) == 0) && (num_places != 0))
//        {
////            Serial.print("_");
//        }
    }
//    Serial.println();
}
