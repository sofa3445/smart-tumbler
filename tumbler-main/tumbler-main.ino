#include "DHT.h"
int temp_pin = A0;
DHT dht(temp_pin, DHT11); //DHT 설정. DHT dht(핀번호, DHT종류)

int trigpin=6;
int echopin=7;

int led1 =11;
int led2 =10;
int led3 =9;
int rgb_r = 4; //rgb 중 빨간색
int rgb_g = 3; //`` 초록색
int rgb_b = 2; //`` 파란색

void setup() {
 Serial.begin(9600);
  
 pinMode(trigpin, OUTPUT);
 pinMode(echopin,INPUT);
 
 pinMode(led1,OUTPUT);
 pinMode(led2,OUTPUT);
 pinMode(led3,OUTPUT);
 pinMode(rgb_r,OUTPUT);
 pinMode(rgb_g,OUTPUT);
 pinMode(rgb_b,OUTPUT);

 delay(1000);
}

void loop() {
  
  int temp = dht.readTemperature(); //온도 변수 선언,초기화
  Serial.print("Temperature: "); //시리얼 모니터에 2초간 온도 표시
  Serial.print(temp);
  Serial.println(" C");
  
  int duration,distance;
  digitalWrite(trigpin,HIGH);
  
  delayMicroseconds(1000);
  digitalWrite(trigpin,LOW);
  
  duration=pulseIn(echopin,HIGH);

  distance=(duration / 2) / 29.1;
  Serial.print("cm: ");
  Serial.println(distance);

  if(temp<50){ // // 49도 이하일수록 파란색
  analogWrite(rgb_g,temp*3);
  analogWrite(rgb_b,temp*5);
  }
  else if(temp>49 && temp<61){ //50~60도 일때 초록색
  analogWrite(rgb_r,temp*2);
  analogWrite(rgb_g,temp*3);
  }
  else if(temp>61){ //61도 이상일때 빨간색
  analogWrite(rgb_r,temp*3);
  analogWrite(rgb_g,temp*2);
  }

  
  if( (distance >0) &&  (distance <= 3) )
  {
   digitalWrite(led1,LOW);
   digitalWrite(led2,HIGH);
   digitalWrite(led3,HIGH);
  } else
  if( (distance > 3) && (distance <= 6)) 
  {
  digitalWrite(led1,HIGH);
  digitalWrite(led2,LOW);
  digitalWrite(led3,HIGH);
  } else
  if( (distance > 6) && (distance <= 12) )
  {
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,LOW);
  }
}
