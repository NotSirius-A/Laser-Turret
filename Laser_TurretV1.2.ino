#include <Servo.h> 
#include <LiquidCrystal.h>

//variables
int XaR = 0;
int Xmapped = 0;
int tickX = 0;

int YaR = 0;
int Ymapped = 0;
int tickY = 0;

int PotentiometerRead = 0;
int tickSpeed = 0;

//temp
int Vo;    
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

//lcd
long interval = 1000;
long previousMillis = 0; 
  /*long interval2 = 50;  not used; keep it for no reason*/

//pins
const int servo1Pin = 9;    
const int servo2Pin = 10;   
const int thermistorPin = A0;
const int potentiometerPin = A2;
const int XreadPin = A4;
const int YreadPin = A5;

//declared servos

Servo Servo1; 
Servo Servo2;

//LCD setup

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup(){ 
 
   
   Servo1.attach(servo1Pin);  
   Servo2.attach(servo2Pin); 
   
  
   lcd.begin(16, 2);

   
}
void loop(){ 

 //Speed Calibration ----------------

 PotentiometerRead = analogRead(potentiometerPin);

 tickSpeed = map(PotentiometerRead, 0, 1015, 1, 11);   
 

 //Servo 1 control ------------------

   XaR = analogRead(XreadPin) +15;
    
    Xmapped = map(XaR, 0, 1000, -tickSpeed, tickSpeed);
  
      tickX -= Xmapped ;
      tickX = constrain(tickX, -90, 90); 
            
   Servo1.write(90 + tickX);
 
 
 //Servo 2 control ------------------   
  
   YaR = analogRead(YreadPin) +15;
   
    Ymapped = map(YaR, 0, 1000, -tickSpeed, tickSpeed);
  
       tickY += Ymapped ;
       tickY = constrain(tickY, -90, 90);    
 
   Servo2.write(90 + tickY); 

 //Thermometer ----------------------

 
  Vo = analogRead(thermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
 
 //LCD control ---------------------
  
  unsigned long currentMillis = millis();

   
    if (currentMillis - previousMillis > interval)
    {
      previousMillis = currentMillis; 
      lcd.clear();
      lcd.print("Temp = ");
      lcd.print(T);
      lcd.print(" C  ");
      }
      
      lcd.setCursor(0,1);
      lcd.print("X = ");
      lcd.print(tickX);
      lcd.setCursor (9,1);
      lcd.print("Y = ");
      lcd.print(tickY);
      
   
   
     
      
      delay(80);  //Servo smoothing, higher = slower 
  
    
}
