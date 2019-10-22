int trig=11;
int echo=12;
int led1=6; //RED
int led2=9; //BLUE

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trig, HIGH); //초음파 발생
  delayMicroseconds(10); //0.01초 대기
  digitalWrite(trig, LOW); //초음파 멈춤
 
  int distance = pulseIn(echo, HIGH) * 17 /1000;

  Serial.print(distance);
  Serial.print("cm");
  Serial.println();

  if(distance > 20)
  {
    digitalWrite(led2, LOW);
    digitalWrite(led1, LOW);
  }
  if(distance > 15 & distance <= 20)
  {
    digitalWrite(led2, HIGH);
    digitalWrite(led1, LOW);
  }
  if(distance > 7 & distance <= 15)
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
  }
  if(distance > 0 & distance <= 7)
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    delay(100);
    digitalWrite(led2, HIGH);
    digitalWrite(led1, LOW);
    delay(100);
  }
} 
