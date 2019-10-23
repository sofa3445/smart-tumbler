#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <DHT.h>
#define BLYNK_PRINT Serial
#include <BlynkSimpleStream.h>

int temp_pin = A0;
DHT dht(temp_pin, DHT11); //DHT 설정. DHT dht(핀번호, DHT종류)
int trigpin=6;
int echopin=5;

int led1 =9;
int led2 =10;
int led3 =11;
int rgb_r = 4; //rgb 중 빨간색
int rgb_g = 3; //`` 초록색
int rgb_b = 2; //`` 파란색

char auth[] = "blsfwPaH3WLWbKO6IUdtimB5z4b32gDE";

SoftwareSerial SwSerial(7, 8); // RX, TX
SoftwareSerial BTSerial(7, 8); //Connect HC-06 TX,RX

LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display

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
 pinMode(rgb_r,OUTPUT);
 pinMode(rgb_g,OUTPUT);
 pinMode(rgb_b,OUTPUT);
 
 SwSerial.begin(9600);
 Blynk.begin(SwSerial, auth);
 delay(1000);
}

/* time */
unsigned long prevReceivedTime = 0;
unsigned long curReceivedTime = 0;
int currentLine = 0;  // Display character at 0 or 1 line
 

void loop() {

  Blynk.run();
  
  int temp = dht.readTemperature(); //온도 변수 선언,초기화
  
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

  Serial.print("Temperature: "); //시리얼 모니터에 온도 표시
  Serial.print(temp);
  Serial.println(" C");
  
  distance=(duration / 2) / 29.1;
  Serial.print("cm: "); //시리얼 모니터에 뚜껑부터 수면까지의 거리 표시
  Serial.println(distance);

/******************** led 제어 ***************************/

  if(temp<50){ // 49도 이하일수록 파란색
  analogWrite(rgb_g,temp);
  analogWrite(rgb_b,100-temp);
  }
  else if(temp>49 && temp<61){ //50~60도 일때 초록색
  analogWrite(rgb_r,temp/2);
  analogWrite(rgb_g,temp);
  analogWrite(rgb_b,100-temp);
  }
  else if(temp>61){ //61도 이상일때 빨간색
  analogWrite(rgb_r,temp);
  analogWrite(rgb_g,100-temp);
  }
///뚜껑에 초음파센서를 부착하며 1번led가 맨아래
  if( (distance >0) &&  (distance <= 3) )///물이 충분할때
  {digitalWrite(led1,HIGH);
   digitalWrite(led2,HIGH);
   digitalWrite(led3,HIGH);
  /// digitalWrite(led4,HIGH);
  } else
  if( (distance > 3) && (distance <= 6))///물 중간
  {
  digitalWrite(led1,LOW);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,HIGH);
  ///digitalWrite(led4,HIGH);
  } else
  if( (distance > 6) && (distance <= 9 ) )///물 중간
  {
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,HIGH);
    ///digitalWrite(led4,HIGH);
  }
  if( (distance > 9) && (distance <= 15 ) )///물 부족
  {
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    ///digitalWrite(led4,HIGH);
  }

}
