#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

int trigpin=6;
int echopin=7;

int led1 =9;
int led2 =10;
int led3 =11;
///int led4=3;

LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display
 
SoftwareSerial BTSerial(2, 3); //Connect HC-06 TX,RX

void setup() {
 Serial.begin(9600);
  Serial.println("good day!");
  BTSerial.begin(9600);  // set the data rate for the BT port
 
  lcd.init();                      // initialize the lcd
 
  lcd.backlight();
  lcd.print("Have a good day"); // Print initial message.
  
 pinMode(trigpin, OUTPUT);
 pinMode(echopin,INPUT);
 
 pinMode(led1,OUTPUT);
 pinMode(led2,OUTPUT);
 pinMode(led3,OUTPUT);
 ///pinMode(led4,OUTPUT);

 delay(1000);
}

/* time */
unsigned long prevReceivedTime = 0;
unsigned long curReceivedTime = 0;
int currentLine = 0;  // Display character at 0 or 1 line
 

void loop() {

  // BT --> Data --> Arduino --> LCD
  if (BTSerial.available()) {
    char c = BTSerial.read();
 
    curReceivedTime = millis();
    if(curReceivedTime - prevReceivedTime > 1000) {  // (1)
      currentLine++;
      if(currentLine > 1) {
        currentLine = 0;
        lcd.clear();
      }
      lcd.setCursor(0, currentLine);
    }
 
    Serial.print(c);
    lcd.write(c);
 
    prevReceivedTime = curReceivedTime;
  }
 
  // PC --> Data --> Arduino --> Data --> BT
  if (Serial.available()) {
    BTSerial.write(Serial.read());  // (2)
  }
  int duration,distance;
  digitalWrite(trigpin,HIGH);
  
  delayMicroseconds(1000);
  digitalWrite(trigpin,LOW);
  
  duration=pulseIn(echopin,HIGH);

  distance=(duration / 2) / 29.1;
  Serial.println("cm: ");
  Serial.println(distance);
 ///뚜껑에 초음파센서를 부착하며 1번led가 맨아래
  if( (distance >0) &&  (distance <= 3) )///물이 충분할때
  {digitalWrite(led1,LOW);
   digitalWrite(led2,LOW);
   digitalWrite(led3,LOW);
  /// digitalWrite(led4,LOW);
  } else
  if( (distance > 3) && (distance <= 6))///물 중간
  {
  digitalWrite(led1,HIGH);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  ///digitalWrite(led4,LOW);
  } else
  if( (distance > 6) && (distance <= 9 ) )///물 중간
  {
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,LOW);
    ///digitalWrite(led4,LOW);
  }
  if( (distance > 9) && (distance <= 15 ) )///물 부족
  {
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,HIGH);
    ///digitalWrite(led4,LOW);
  }


  
}
