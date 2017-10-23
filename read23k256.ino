#include <SPI.h>
 
//SRAM opcodes
#define RDSR 5
#define WRSR 1
#define READ 3
#define WRITE 2
 
uint8_t SpiRAMRead8(uint16_t address) {
  uint8_t read_byte;
 
//  PORTB &= ~(1<<PORTB2); //set SPI_SS low
  SPI.transfer(READ);
  SPI.transfer((char)(address >> 8));
  SPI.transfer((char)address);
  read_byte = SPI.transfer(0xFF);
//  PORTB |= (1<<PORTB2); //set SPI_SS high
  return read_byte;
}
 
void SpiRAMWrite8(uint16_t address, uint8_t data_byte) {
//  PORTB &= ~(1<<PORTB2); //set SPI_SS low
  SPI.transfer(WRITE);
  SPI.transfer((char)(address >> 8));
  SPI.transfer((char)address);
  SPI.transfer(data_byte);
//  PORTB |= (1<<PORTB2); //set SPI_SS high
}
 
void setup(void) {
  uint16_t addr;
  uint8_t i;
 
  Serial.begin(9600);
  SPI.begin();

  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  delay(1000);
  
  for (addr=0; addr<32; addr++) {
    SpiRAMWrite8(addr, (uint8_t)addr);
    Serial.print("Addr: ");
    Serial.print(addr);
    i = SpiRAMRead8(addr);
    Serial.print(" | Read: ");
    Serial.println((uint16_t)i);
  }

  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
}
 
void loop() {
}

//#include <SPI.h>
// 
////SRAM opcodes
//#define RDSR        5
//#define WRSR        1
//#define READ        3
//#define WRITE       2
// 
//byte cs_pin[1] = {10}; //cs_pin location of the two SRAMS
//
//uint32_t maxram = 131072; //number of bytes in 23LC1024 SRAM
//uint32_t maxpage = 4096;  //number of pages in 23LC1024 SRAM
//
///*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-*/
////Page transfer Functions
////here we can read and write 32 bytes at each address
//
//void Spi23LC1024Read32(uint32_t address, uint8_t cs_pin, uint8_t* buff)
//{
//  uint32_t i; 
//  uint8_t read_page; 
//
//  digitalWrite(cs_pin, LOW);  
//  SPI.transfer(READ);
//  SPI.transfer((uint8_t)(address >> 16));
//  SPI.transfer((uint8_t)(address >> 8)); 
//  SPI.transfer((uint8_t)address);
//  
//  for (i = 0; i < 32; i++)
//  {
//      read_page = SPI.transfer(0x00);
//      buff[i] = read_page;
////      Serial.println(read_page);
//  }
//  digitalWrite(cs_pin, HIGH);   
//}
//
//void Spi23LC1024Write32(uint32_t address, uint8_t* buffer170, uint8_t cs_pin)
//{
//    uint32_t i;
//    
//    digitalWrite(cs_pin, LOW); 
//    SPI.transfer(WRITE);
//    SPI.transfer((uint8_t)(address >> 16));
//    SPI.transfer((uint8_t)(address >> 8));
//    SPI.transfer((uint8_t)address);
//    
//    for (i = 0; i < 32; i++)
//    {
//        SPI.transfer(buffer170[i]);
//    }
//    digitalWrite(cs_pin, HIGH); 
//}
///*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-*/
//
//uint32_t i, j, n; 
//uint32_t value; 
//uint32_t num = 0; 
//uint32_t total_send = 10; 
//uint8_t buff[32];
//uint8_t buffer170[32] = {170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170}; 
//
//void setup(void) 
//{
//  Serial.begin(9600);
//  SPI.begin();
//
//  pinMode(10, OUTPUT);
////  digitalWrite(10, HIGH);
//  digitalWrite(10, LOW);
//  delay(1000);
//  Serial.println("PAGE MODE");
//  
//  num = 0;
//  for (i = 0; i < 1; i++)
//  { 
//    Spi23LC1024Write32(i, buffer170, cs_pin[j]);
//  }
//  for (i = 0; i < 1; i++) 
//  {
//    Spi23LC1024Read32(i, cs_pin[j], buff);
//    // each page consists of 32 bytes 
//    for (n = 0; n < 32; n++)  
//    {
//      Serial.println(buff[n],DEC);
////      Serial.println(buff[n],HEX);
////      print_binary(buff[n],8);
//    }
////    if ((i+1)%2==0)
////      Serial.println();
//  }
//
//  Serial.println("FINISH");
////  delay(1000); //To give the cs_line time to die down
//  digitalWrite(10, HIGH);
//
//}
// 
//void loop() 
//{
//
//}
//
//void print_binary(int v, int num_places)
//{
//    int mask=0, n;
//
//    for (n=1; n<=num_places; n++)
//    {
//        mask = (mask << 1) | 0x0001;
//    }
//    v = v & mask;  // truncate v to specified number of places
//
//    while(num_places)
//    {
//
//        if (v & (0x0001 << num_places-1))
//        {
//             Serial.print("1 ");
//        }
//        else
//        {
//             Serial.print("0 ");
//        }
//
//        --num_places;
////        if(((num_places%4) == 0) && (num_places != 0))
////        {
//////            Serial.print("_");
////        }
//    }
////    Serial.println();
//}
