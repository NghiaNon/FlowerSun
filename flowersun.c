#include <Wire.h>  
#include <LiquidCrystal_I2C.h> 
#include "DHT.h"  
#include <Servo.h>  
//Servo 
Servo servo; // servo object representing the MG 996R servo 
//DHT11 
const int DHTPIN = 3;       
const int DHTTYPE = DHT11;  
DHT dht(DHTPIN, DHTTYPE); 
//LCD 
LiquidCrystal_I2C lcd(0x27,16,2);  
void setup() 
{ 
//Servo + LDR 
servo.attach(5); // servo is wired to Arduino on digital pin 3 
Serial.begin(9600); 
//DHT11 
dht.begin(); 
//LCD 
lcd.init();                       
lcd.backlight(); 
lcd.setCursor(0,0); 
lcd.print("FLOWER ROAD!!!"); 
lcd.setCursor(0,1); 

 
  lcd.print("LOADING..."); 
  delay(5000); 
  lcd.clear(); 
} 
 
void loop() 
{ 
  //DHT11 
  float h = dht.readHumidity();     
  float t = dht.readTemperature(); 
 
  //SERVO + LDR 
  int value5 = analogRead(A3);     // read sensor value 
  int value4 = analogRead(A2);     // read sensor value 
  int value3 = analogRead(A1);     // read sensor value 
  int value2 = analogRead(A0);     // read sensor value 
 
  int percent5 = map(value5, 0, 1023, 0, 100); // convert to % 
  int percent4 = map(value4, 0, 1023, 0, 100); // convert to % 
  int percent3 = map(value3, 0, 1023, 0, 100); // convert to % 
  int percent2 = map(value2, 0, 1023, 0, 100); // convert to % 
 
  int ar[4] = {percent2, percent3, percent4, percent5}; 
 
  int lightMax = min(ar[0],min(ar[1], min(ar[2],ar[3]))); 
  int lightMin = max(ar[0],max(ar[1], max(ar[2],ar[3]))); 
 
  Serial.println(ar[0]); 
  Serial.println(ar[1]); 
  Serial.println(ar[2]);  
 
  Serial.println(ar[3]); 
 
  Serial.println(lightMax); 
  Serial.println(lightMin); 
  Serial.println("------------------------------------------"); 
 
  servo.write(90);   
  if(lightMin-lightMax>=30){ 
    //A2 
    if(ar[0]==lightMax){ 
      servo.write(0); 
    } 
    //A3 
    else if(ar[1]==lightMax){ 
      servo.write(180); 
    } 
    //A4 
    else if(ar[2]==lightMax){ 
      servo.write(180); 
    } 
    //A5 
    else if(ar[3]==lightMax){ 
      servo.write(0); 
    } 
  }else{ 
    servo.write(90); 
  } 
  delay(1000); 
  lcd.clear(); 
 
  //LCD 
  lcd.setCursor(0,0); 
  lcd.print("Humi:"); 
  lcd.setCursor(12,0); 
  lcd.print("RH"); 
 
  lcd.setCursor(0,1); 
  lcd.print("Temp:"); 
  lcd.setCursor(12,0); 
  lcd.print(".C"); 
 
  lcd.setCursor(6,0); 
  lcd.print(h); 
 
  lcd.setCursor(6,1); 
  lcd.print(t); 
 
  delay(1000); 
  lcd.clear(); 
} 