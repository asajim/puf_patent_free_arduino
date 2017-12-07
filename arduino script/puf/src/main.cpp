#include "Arduino.h"
#include <stdio.h>
#include <BCH.h>
#include <SPI.h>

#define RDSR        5
#define WRSR        1
#define READ        3
#define WRITE       2

byte cs_pin = 10; //cs_pin location of the two SRAMS
uint32_t maxpage = 4096;  //number of pages in 23LC1024 SRAM
uint32_t i, j, n;
uint32_t value;
uint32_t num = 0;
uint32_t total_send = 10;
// uint8_t buff[32];
uint32_t index = 0;
long puf_index_default1[21] = {
  10204, 10328, 10452, 10576,
  10700, 10824, 10948, 11072,
  28796, 28920, 29044, 29168,
  29292, 29416, 29540, 29664,
  79804, 79928, 80052, 80176,
  80300,  };
long puf_index_default2[16] = {
  80424, 80548, 80672,
  85788, 85912, 86036, 86160,
  86284, 86408, 86532, 86656,
  89052, 89176, 89300, 89424,
  89548};
uint8_t puf_binary_default1[21*32] = {
  1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0,
  0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1,
  1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0,
  1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1,
  1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1,
  1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1,
  0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,
  1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1,
  0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0,
  0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0,
  0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0,
  0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0,
  1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1,
  0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0,
  1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1,
  1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0,
  };

uint8_t puf_binary_default2[16*32] = {
  1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0,
  1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0,
  0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0,
  1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1,
  0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1,
  0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1,
  0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1,
  0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1,
  1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1,
  1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1,
  1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1,
  1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1,
  0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0,
  0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0,
  1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1,
};
uint8_t puf_binary[32*37];
int inByte;

int pin_hold = 11;
int pin_select = 10;
int pin_mosfet = 12;
int pin_power = 8;

int8_t * int_to_binary(int value, int length){
  int8_t * result = (int8_t*)malloc(sizeof(int8_t)*length);
  for (int i = 0; i < length; ++i) {
    result[length-1-i] = (value >> i) & 1;
  }

  return result;
}

int difference_array(int8_t a[], int8_t b[], int size) {
  int count = 0;
  for (int i = 0; i < size; i++) {
    if (a[i] != b[i]) {
      count++;
    }
  }
  return count;
}

void print_array(int8_t input[], int size) {
  for (int i = 0; i < size; i++) {
    Serial.print(input[i]);
  }
  Serial.println();
}

void print_binary(uint8_t v)
{
  int num_places = 8;
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
      Serial.print("1");
    }
    else
    {
      Serial.print("0");
    }

    --num_places;
    if(((num_places%4) == 0) && (num_places != 0))
    {
      Serial.print(" ");
    }
  }
  Serial.println();
}

void store_binary_puf(uint8_t v, int index)
{
  Serial.print(index);
  Serial.print(" - \t");
  int num_places = 8;
  int mask=0, n,i;

  for (n=1; n<=num_places; n++)
  {
    mask = (mask << 1) | 0x0001;
  }
  v = v & mask;  // truncate v to specified number of places

  i=0;
  while(num_places)
  {
    if (v & (0x0001 << num_places-1))
    {
      puf_binary[i+index]=1;
      Serial.print("1");
    }
    else
    {
      Serial.print("0");
      puf_binary[i+index]=0;
    }

    --num_places;
    i++;
  }
  Serial.println();
}

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

  return read_byte;
}

void readSRAM(){
  uint8_t result;

  SPI.begin();
  digitalWrite(pin_select, LOW);
  digitalWrite(pin_hold, HIGH);
  digitalWrite(pin_mosfet, HIGH);
  digitalWrite(pin_power, HIGH);
  delay(100);

  // read
  // index = 0;
  Serial.println();
  Serial.println();
  for (i = 0; i < 21; i++)
  {
    result = Spi23LC1024Read8(puf_index_default1[i], cs_pin);
    store_binary_puf(result, i*32);
    result = Spi23LC1024Read8(puf_index_default1[i]+1, cs_pin);
    store_binary_puf(result, (i*32)+8);
    result = Spi23LC1024Read8(puf_index_default1[i]+2, cs_pin);
    store_binary_puf(result, (i*32)+16);
    result = Spi23LC1024Read8(puf_index_default1[i]+3, cs_pin);
    store_binary_puf(result, (i*32)+24);
  }

  for (i = 0; i < 16; i++)
  {
    int j = i+21;
    result = Spi23LC1024Read8(puf_index_default2[i], cs_pin);
    store_binary_puf(result, j*32);
    result = Spi23LC1024Read8(puf_index_default2[i]+1, cs_pin);
    store_binary_puf(result, (j*32)+8);
    result = Spi23LC1024Read8(puf_index_default2[i]+2, cs_pin);
    store_binary_puf(result, (j*32)+16);
    result = Spi23LC1024Read8(puf_index_default2[i]+3, cs_pin);
    store_binary_puf(result, (j*32)+24);
  }

  digitalWrite(pin_select, HIGH);
  //  digitalWrite(pin_hold, LOW);
  digitalWrite(pin_hold, HIGH);
  digitalWrite(pin_mosfet, LOW);
  digitalWrite(pin_power, LOW);

  SPI.end();
}

void set(){
  Serial.begin(9600);

  delay(1000);

  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(pin_select, OUTPUT);
  pinMode(pin_hold, OUTPUT);
  pinMode(pin_mosfet, OUTPUT);
  pinMode(pin_power, OUTPUT);
}

void check_difference(){
  Serial.println();
  int max_diff = 0;
  for (int i=0;i<21*32;i=i+32){
    int diff=difference_array(&puf_binary[i], &puf_binary_default1[i], 32);
    if (diff > max_diff){
      max_diff = diff;
    }

    Serial.print(i);
    Serial.print(" - ");
    Serial.print(diff);
    Serial.println(", ");
  }
  Serial.print("Max difference: ");
  Serial.println(max_diff);

  for (int i=21*32;i<37*32;i=i+32){
    int diff=difference_array(&puf_binary[i], &puf_binary_default2[i-21*32], 32);
    if (diff > max_diff){
      max_diff = diff;
    }

    Serial.print(i);
    Serial.print(" - ");
    Serial.print(diff);
    Serial.println(", ");
  }
  Serial.print("Max difference: ");
  Serial.println(max_diff);
}

void setup(void)
{
  set();

  readSRAM();

  check_difference();
  Serial.println();


  // BCH bch;
  //
  // int m = bch.get_m();
  // int n = bch.get_n();
  // int k = bch.get_key_length();
  // int t = bch.get_t();
  // Serial.println(m);
  // Serial.println(n);
  // Serial.println(k);
  // Serial.println(t);
  // int8_t *encoded = (int8_t *) malloc(sizeof(int8_t) * n);
  //
  // bch.initialize();               /* Read m */
  //
  // int total_diff = 0;
  // int total_trial = 0;
  //
  // for (int f=0;f<pow(2,k);f++) {
  //     int8_t * key = int_to_binary(f,k);
  //
  //     bch.encode_bch(key, encoded);           /* encode data */
  //     print_array(key,k);
  //     print_array(encoded,n);
  //   //   int diff_input, diff_key;
  //   //   for (int g = 0; g < 100; g++) {
  //   //       int range_from = 0;
  //   //       int range_to = n;
  //   //       for (int h=1;h<=t;h++) {
  //   //           int count = h;
  //   //           // int *errors = generate_random(range_from, range_to, count);
  //   //
  //   //           int8_t *encoded_r = (int8_t *) malloc(sizeof(int8_t) * n);
  //   //           memcpy(encoded_r, encoded, sizeof(int8_t) * n);
  //   //           // for (int i = 0; i < count; i++) {
  //   //           //     encoded_r[errors[i]] = encoded_r[errors[i]] == 1 ? 0 : 1;
  //   //           // }
  //   //
  //             int8_t *key_r = (int8_t *) malloc(sizeof(int8_t) * k);
  //             bch.decode_bch(encoded, key_r);
  //             print_array(key_r,k);
  //   //
  //   //           diff_key = difference_array(key, key_r, k);
  //   //           if (diff_key > 0)
  //   //               total_diff += 1;
  //   //           total_trial += 1;
  //   //       }
  //   //   }
  //   }
  // Serial.print("Total trial: ");
  // Serial.println(total_trial);
  // Serial.print("Total diff: ");
  // Serial.println(total_diff);
}



void loop(){

}
