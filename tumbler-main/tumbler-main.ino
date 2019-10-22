int trigpin=6;
int echopin=7;

int led1 =11;
int led2 =10;
int led3 =9;

void setup() {
 Serial.begin(9600);
  
 pinMode(trigpin, OUTPUT);
 pinMode(echopin,INPUT);
 
 pinMode(led1,OUTPUT);
 pinMode(led2,OUTPUT);
 pinMode(led3,OUTPUT);

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

  if( (distance >0) &&  (distance <= 3) )
  {digitalWrite(led1,LOW);
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
