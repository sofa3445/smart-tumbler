int trigpin=6;
int echopin=7;

int led1 =9;
int led2 =10;
int led3 =11;
int led4=3;

void setup() {
 Serial.begin(9600);
  
 pinMode(trigpin, OUTPUT);
 pinMode(echopin,INPUT);
 
 pinMode(led1,OUTPUT);
 pinMode(led2,OUTPUT);
 pinMode(led3,OUTPUT);
 pinMode(led4,OUTPUT);

 delay(1000);
}

void loop() {
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
   digitalWrite(led4,LOW);
  } else
  if( (distance > 3) && (distance <= 6))///물 중간
  {
  digitalWrite(led1,HIGH);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(led4,LOW);
  } else
  if( (distance > 6) && (distance <= 9 ) )///물 중간
  {
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,LOW);
    digitalWrite(led4,LOW);
  }
  if( (distance > 9) && (distance <= 15 ) )///물 부족
  {
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,HIGH);
    digitalWrite(led4,LOW);
  }
}
