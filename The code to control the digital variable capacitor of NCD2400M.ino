
#include "Wire.h"
const int address = 0x60;

void TCA9548A(uint8_t bus)
{
  Wire.beginTransmission(0x70); 
  Wire.write(1 << bus);
  Wire.endTransmission();
}

#define oscil_code 0
#define coil1_code 0//가까워지는
#define coil2_code 0 // 중간
#define coil3_code 0 // 멀어지는

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);
  Serial.println("Write 0x5 to volatilte memory:");
  TCA9548A(2);
  Wire.beginTransmission(address);
  Wire.write(coil1_code/0x100);
  Wire.write(coil1_code%0x100);
  Wire.endTransmission();
  TCA9548A(3);
  Wire.beginTransmission(address);
  Wire.write(coil2_code/0x100);
  Wire.write(coil2_code%0x100);
  Wire.endTransmission();
  TCA9548A(4);
  Wire.beginTransmission(address);
  Wire.write(coil3_code/0x100);
  Wire.write(coil3_code%0x100);
  Wire.endTransmission();
  TCA9548A(5);
  Wire.beginTransmission(address);
  Wire.write(oscil_code/0x100);
  Wire.write(oscil_code%0x100);
  Wire.endTransmission();  
}

//한바이트 데이터를 임시 저장
char cTemp;
//완성된 명령어
String sCommand = "";
String sTemp = "";

void loop() {
  // put your main code here, to run repeatedly:
  sCommand = "";
  
  while(Serial.available()>0) {
    cTemp = Serial.read();
    sCommand.concat(cTemp);
    delay(10);
  }
  
  if(sCommand != "" ) { //완성된 데이터가 있다. 
    char cTempData[4];
    sCommand.toCharArray(cTempData, 4);
    int value = atoi(cTempData);

    if (0 <= value && value <=511) {
      TCA9548A(5);
      Wire.beginTransmission(address);
      Wire.write(value/0x100);
      Wire.write(value%0x100);
      Wire.endTransmission();
      Serial.print("variable cap value : ");
      Serial.println(value);
    }
    else {
      Serial.println("Wrong value");    
    }
  }
}
