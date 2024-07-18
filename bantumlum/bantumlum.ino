const int trig = 31; 
const int echo = 30; 
unsigned long thoigian; 
int khoangcach; 

const int trig1 = 41; 
const int echo1 = 42; 
unsigned long thoigian1; 
int khoangcach1; 


#include <MPU6050_tockn.h>
#include <Wire.h>
MPU6050 mpu6050(Wire);
int x, y, z;

int den = 12;
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

const int stepX = 2;
const int dirX  = 5;

void setup() 
{
  Serial.begin(9600);   
  lcd.init(); 
  lcd.backlight(); 
  pinMode(trig, OUTPUT); 
  pinMode(echo, INPUT); 
  pinMode(den, OUTPUT);
  pinMode(trig1, OUTPUT); 
  pinMode(echo1, INPUT); 
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}

void loop() 
{
  {
  digitalWrite(trig,0); 
  delayMicroseconds(2); 
  digitalWrite(trig,1); 
  delayMicroseconds(10); 
  digitalWrite(trig,0);
  thoigian = pulseIn (echo, HIGH);
  khoangcach = int (thoigian / 2 / 29.412); 
  Serial.print("Khoảng cách: ");
  Serial.print(khoangcach);
  Serial.println("cm");

  digitalWrite(trig1,0); 
  delayMicroseconds(2); 
  digitalWrite(trig1,1); 
  delayMicroseconds(10); 
  digitalWrite(trig1,0);
  thoigian1 = pulseIn (echo, HIGH);
  khoangcach1 = int (thoigian1 / 2 / 29.412); 
  Serial.print("Khoảng cách: ");
  Serial.print(khoangcach1);
  Serial.println("cm");
}
{
  mpu6050.update();
  x = mpu6050.getAngleX();
  y = mpu6050.getAngleY();
  z = mpu6050.getAngleZ();
  Serial.print("X: "); Serial.print(x); Serial.print("      ");
  Serial.print("Y: "); Serial.print(y); Serial.print("      ");
  Serial.print("Z: "); Serial.println(z);
}
  {
 lcd.init(); 
  lcd.setCursor(1,0);
  lcd.print("KC1:");
  lcd.setCursor(6,0);
  lcd.print(khoangcach);
   lcd.setCursor(11,0);
  lcd.print("KC2:");
  lcd.setCursor(17,0);
  lcd.print(khoangcach1);
  lcd.setCursor(0,1);
  lcd.print("X: ");
  lcd.setCursor(3,1);
  lcd.print(x);
  lcd.setCursor(6,1);
  lcd.print("Y: ");
  lcd.setCursor(9,1);
  lcd.print(y);
  lcd.setCursor(12,1);
  lcd.print("Z: ");
  lcd.setCursor(16,1);
  lcd.print(z);
  lcd.setCursor(0,2);
  lcd.print("Arduino LCM IIC 2004");
   lcd.setCursor(2,3);
  lcd.print("Power By Ec-yuan!"); 
  }
  {
  digitalWrite(stepX,HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepX,LOW);
    delayMicroseconds(1000);
  }
}
