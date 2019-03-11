#include <AFMotor.h>

//motor sheild
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

const int trigPin = A9;
const int echoPin = A8;
long duration;
int distance;

//Bluetooth 
char bt='S';

//Color sensor
const int s0=22;
const int s1=23;
const int s2=24;
const int s3=25;
const int sensorData=26;
int dataR=0;
int dataG=0;
int dataB=0;



void setup() {
  
 Serial.begin(9600);

  Stop();
 
  //Distance setup
  pinMode(trigPin,OUTPUT); // Sender 
  pinMode(echoPin,INPUT); // Receiver    

  //Color setup
   pinMode(s0,OUTPUT);
   pinMode(s1,OUTPUT);
   pinMode(s2,OUTPUT);
   pinMode(s3,OUTPUT);
   pinMode(sensorData,INPUT);
   digitalWrite(s0,HIGH);
   digitalWrite(s1,HIGH);


}

void loop() {
   bt=Serial.read();
   
 //Detect Color 
   digitalWrite(s2,LOW);
   digitalWrite(s3,LOW);
   dataR=pulseIn(sensorData,LOW);
   

   digitalWrite(s2,HIGH);
   digitalWrite(s3,HIGH);
   dataG=pulseIn(sensorData,LOW);

   digitalWrite(s2,LOW);
   digitalWrite(s3,HIGH);
   dataB=pulseIn(sensorData,LOW);

if(isRed() || isYellow() || isGreen()){
  if(isRed()){
    Stop();
    }
  else if (isYellow()){
    motor1.setSpeed(100);
    motor2.setSpeed(100);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    delay(1000);
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    Stop();
    }
  else if(isGreen()){
    forward();
    }
  
  }
         if(bt=='F')
          {
              forward();
          }

          if(bt=='B')
          {
            backward(); 
          }

           if(bt=='L')
            {
              left(); 
            }

           if(bt=='R')
           {
              right(); 
           }

           if(bt=='S')
           {
              Stop(); 
           }
}
//Functions
//Bluetooth
void forward()
{
      digitalWrite(trigPin, LOW);
   
      digitalWrite(trigPin, HIGH);
      
      digitalWrite(trigPin, LOW);

      duration = pulseIn(echoPin, HIGH);
      distance= duration*0.034/2;
      if(distance<=10)
      {
        Stop();
      }
      else if(distance>=11 && distance<=20)
      {
        motor1.setSpeed(100);
        motor2.setSpeed(100);
        motor1.run(FORWARD);
        motor2.run(FORWARD);
      }
      else if(distance>=21 && distance<=25)
      {
        motor1.setSpeed(150);
        motor2.setSpeed(150);
        motor1.run(FORWARD);
        motor2.run(FORWARD);
      }
      else
      {
        motor1.setSpeed(250);
        motor2.setSpeed(250);
        motor1.run(FORWARD);
        motor2.run(FORWARD);
      }
  
       
}
        
   
void backward()
{
  motor1.setSpeed(250);
  motor2.setSpeed(250);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
}
void left()
{
  motor1.setSpeed(250);
  motor2.setSpeed(250);
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
}
void right()
{
  motor1.setSpeed(250);
  motor2.setSpeed(250);
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
}
void Stop()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}


//Detect Red color
bool isRed()
{
  if((dataR<38 && dataR>25) && (dataG<68 && dataG>50) && (dataB<55 && dataB>38))
  {
    return true;
  }
  else
  {
    return false;
  }
}

//Detect Green color

bool isGreen()
{
  if((dataR<50 && dataR>36) && (dataG<53 && dataG>35) && (dataB<52 && dataB>40))
  {
    return true;
  }
  else
  {
    return false;
  }
}
bool isYellow()
{
  if((dataR<31 && dataR>19) && (dataG<48 && dataG>28) && (dataB<48 && dataB>35))
  {
    return true;
  }
  else
  {
    return false;
  }
}
