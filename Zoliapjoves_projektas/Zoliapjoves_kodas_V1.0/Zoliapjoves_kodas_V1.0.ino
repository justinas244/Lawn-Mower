#include <Servo.h>
#include <SharpIR.h>

int pakelimo_pin = A2;
SharpIR sensor( SharpIR::GP2Y0A41SK0F, pakelimo_pin );

#define trigPin 28
#define echoPin 26
#define led 13

int desines = 33;  // BWFR signal
int kaires = 35;  // BWFL signal

unsigned long BWFR_count;
unsigned long BWFL_count;

int L_motor = 9;
int l_motor = 8;
int R_motor = 10;
int r_motor = 11;
 
Servo peilis;
Servo Servas;

int pos = 0;

int kaires_pin = 25;
int kairinis_pin = 24;
int desininis_pin = 23;
int desines_pin = 22;

int kaire,kairinis,desininis,desine;

byte RUN_STATE = 0;

int ribaD = 3000;
int ribaL = 2000;

int mygtuko_pin = A1;
int stopas =0;

int aukstis = 0;
int pakelimas = 7;
int akumo_pin = A0;

float iskrovimo_riba = 11.00;

unsigned long previousMillis = 0;
unsigned long intervalas = 5000;
int k=0;
float akumas,akuma;
float sum=0;

int greitis=1500;
void setup(){
Serial.begin(9600);
 pinMode(kaires_pin, INPUT);
 pinMode(kairinis_pin, INPUT);
  pinMode(desininis_pin, INPUT);
  pinMode(desines_pin, INPUT);
 pinMode(mygtuko_pin, INPUT);
 pinMode(akumo_pin,INPUT);
 
 pinMode(desines , INPUT);
  pinMode(kaires , INPUT);

pinMode(L_motor,OUTPUT);
pinMode(l_motor,OUTPUT);
pinMode(R_motor,OUTPUT);
pinMode(r_motor,OUTPUT); 

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  
   TCCR1A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM20);
  TCCR1B = TCCR1B & 0b11111000 | 0x02;
  delay(2000);
  uzkurimas();
}

void loop(){
  int mygtukas = digitalRead(mygtuko_pin);
  aukstis = sensor.getDistance(); 

 for(int i=1;i<=3;i++){
  int sensorValue = analogRead(akumo_pin);
   akuma = sensorValue * (31.0 / 1024.0);
   sum=sum+akuma;
   delay(10);
 }
 akumas=sum/3;
 sum=0;
 unsigned long currentMillis = millis();
 
    Serial.print("Akumas: ");
    Serial.println(akumas);
 /*if(akumas<=iskrovimo_riba){
    stopas=1;
  }*/
  
  if(aukstis>=pakelimas){
    stopas = 1;
    k=0;
  }
  if(mygtukas==HIGH){
       Serial.println("STOP mygtukas paspaustas");
       peilis.writeMicroseconds(1000);
       motor(0,0);
       delay(2000);
    stopas=1;
    }
  
  if(stopas==0){
    go();
  }
  else{
    while(true){
      Serial.println("Sistema pereina i STOP rezima");
      peilis.writeMicroseconds(1000);
      motor(0,0);
      delay(5000);
    }
  }

}
void go(){
  peilis.writeMicroseconds(greitis);
  BWFR_count = FreqCounter(desines, 100); 
  BWFL_count = FreqCounter(kaires, 100); 

Serial.print(BWFR_count);
Serial.print("    ");
Serial.println(BWFL_count);
Serial.println("-------------------");


if(BWFR_count>=ribaD && BWFL_count<=ribaL){
    motor(0,0);
   laikas(800);
   motor(-170,-170);
  laikas(1700);
   motor(-150,150);
   laikas(1400);
   motor(0,0);
   laikas(100);
}
else if(BWFR_count<=ribaD && BWFL_count>=ribaL){
    motor(0,0);
   laikas(800);
   motor(-170,-170);
   laikas(1700);
   motor(150,-150);
   laikas(1400);
   motor(0,0);
   laikas(100);
}
else if(BWFR_count>=ribaD && BWFL_count>=ribaL){
   motor(0,0);
   laikas(800);
   motor(-170,-170);
   laikas(1200);
   motor(-150,150);
   laikas(1900);
   motor(0,0);
   laikas(100);
}
  else if(BWFR_count<=ribaD && BWFL_count<=ribaL){
   motor(150,150);
   }
}
void laikas(int laikas){
  for(int i=0;i<=laikas/100; i++){
     int mygtukas = digitalRead(mygtuko_pin);
      aukstis = sensor.getDistance();
      if(aukstis>=pakelimas){
        stopas=1;
        } 
     if(mygtukas==HIGH){
       Serial.println("STOP mygtukas paspaustas");
       peilis.writeMicroseconds(1000);
       motor(0,0);
       delay(2000);
    stopas=1;
    }
    if(stopas==1){
      i=laikas/100;;
    }
    delay(100);
  }
}
void uzkurimas(){
   Serial.println("Uzkurimas pradedamas");
  peilis.attach(7);
  peilis.writeMicroseconds(1000);
  delay(3000);
  
  peilis.writeMicroseconds(greitis);
  delay(7000);
  motor(150,150);
  delay(2000);
  Serial.println("Uzkurimas baigtas");
}
unsigned long FreqCounter(int pin, unsigned long gateTime)
{ 
  unsigned long time, timeInitial;
  unsigned long count=0;
  boolean level, lastLevel;
  
  timeInitial = millis();
  time=timeInitial;
    
  while((time-timeInitial)<gateTime) 
  {    
    level = digitalRead(pin);
    if((level != lastLevel) ) // if transient
    { 
       lastLevel = level;
       if(level == HIGH) count++; //rising front
    }
  time=millis();
  }
  return count;
}

void motor(int left, int right){
  
   left=constrain(left, -255, 255);
  right=constrain(right, -255, 255);

  if(left>=0){
    digitalWrite(l_motor,LOW);
    analogWrite(L_motor,left);
  }
  else{
    digitalWrite(l_motor,HIGH);
    analogWrite(L_motor,255+left);
  }
  
  if(right>=0){
    digitalWrite(r_motor,LOW);
    analogWrite(R_motor,right);
  }
  else{
    digitalWrite(r_motor,HIGH);
    analogWrite(R_motor,255+right);
  }
}


